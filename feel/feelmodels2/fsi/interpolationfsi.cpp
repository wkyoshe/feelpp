/* -*- mode: c++; coding: utf-8; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; show-trailing-whitespace: t -*- vim:fenc=utf-8:ft=tcl:et:sw=4:ts=4:sts=4

 This file is part of the Feel library

 Author(s): Vincent Chabannes <vincent.chabannes@feelpp.org>
 Date: 2011-07-05

 Copyright (C) 2011 Université Joseph Fourier (Grenoble I)

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
/**
 \file interpolationfsi.cpp
 \author Vincent Chabannes <vincent.chabannes@feelpp.org>
 \date 2011-07-05
 */

#include <feel/feelmodels2/fsi/interpolationfsi.hpp>


namespace Feel
{
namespace FeelModels
{

template< class FluidType, class SolidType >
InterpolationFSI<FluidType,SolidType>::InterpolationFSI(fluid_ptrtype fluid, solid_ptrtype solid, bool buildOperators)
    :
    M_fluid(fluid),
    M_solid(solid),
    M_worldComm(fluid->worldComm()),
    M_interfaceFSIisConforme( option(_name="fsi.conforming-interface").template as<bool>()),
    M_fsiCouplingType( option(_name="fsi.coupling-type").template as<std::string>()),
    M_fsiCouplingBoundaryCondition( option(_name="fsi.coupling-bc").template as<std::string>() ),
    M_opDispIsInit(false),
    M_opStressIsInit(false),
    M_opVelocityIsInit(false),
    M_verbose(fluid->verbose() || solid->verbose()),
    M_verboseAllProc(fluid->verboseAllProc() || solid->verboseAllProc())
{
    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","constructor", "start",
                                               this->worldComm(),this->verboseAllProc());

    bool doBuild = buildOperators && !this->fluid()->markersNameMovingBoundary().empty();
    if (this->solid()->isStandardModel())
        doBuild = doBuild && !this->solid()->getMarkerNameFSI().empty();

    if ( this->fluid()->doRestart() )
    {
        this->fluid()->getMeshALE()->revertReferenceMesh();
        this->fluid()->getMeshALE()->displacement()->functionSpace()->rebuildDofPoints();
    }

    if ( doBuild )
    {
        boost::mpi::timer btime;double thet;
        if (this->solid()->isStandardModel())
        {
            //---------------------------------------------//
            this->initDispInterpolation();
            std::ostringstream ostr1;ostr1<<btime.elapsed()<<"s";
            if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","initDispInterpolation","done in "+ostr1.str(),
                                                       this->worldComm(),this->verboseAllProc());
            btime.restart();
            //---------------------------------------------//
            this->initStressInterpolation();
            std::ostringstream ostr2;ostr2<<btime.elapsed()<<"s";
            if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","initStressInterpolation","done in "+ostr2.str(),
                                                       this->worldComm(),this->verboseAllProc());
            btime.restart();
            //---------------------------------------------//
            if (this->fsiCouplingType()=="Semi-Implicit" || this->fsiCouplingBoundaryCondition()=="robin-neumann")
            {
                this->initVelocityInterpolation();
                std::ostringstream ostr3;ostr3<<btime.elapsed()<<"s";
                if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","initVelocityInterpolation","done in "+ostr3.str(),
                                                           this->worldComm(),this->verboseAllProc());
            }
            btime.restart();
            //---------------------------------------------//
#if 0
            if (this->fsiCouplingBoundaryCondition()=="robin-neumann")
            {
                this->initStressInterpolationS2F();
                std::ostringstream ostr4;ostr4<<btime.elapsed()<<"s";
                if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","initStressInterpolationS2F","done in "+ostr4.str(),
                                                           this->worldComm(),this->verboseAllProc());

            }
#endif
            //---------------------------------------------//
            if (this->fsiCouplingBoundaryCondition()=="robin-robin")
            {
                this->initVelocityInterpolationF2S();
            }
        }
        else if ( this->solid()->is1dReducedModel() )
        {
            //---------------------------------------------//
            this->initDisp1dToNdInterpolation();
            thet = btime.elapsed();
            if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","initDisp1dToNdInterpolation",
                                                       (boost::format("done in %1%s")% thet).str(),
                                                       this->worldComm(),this->verboseAllProc());
            btime.restart();
            //---------------------------------------------//
            this->initStress1dToNdInterpolation();
            thet = btime.elapsed();
            if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","initStress1dToNdInterpolation",
                                                       (boost::format("done in %1%s")% thet).str(),
                                                       this->worldComm(),this->verboseAllProc());
            btime.restart();
            //---------------------------------------------//
            if (this->fsiCouplingType()=="Semi-Implicit" || this->fsiCouplingBoundaryCondition()=="robin-neumann")
            {
                this->initVelocity1dToNdInterpolation();
                thet = btime.elapsed();
                if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","initVelocity1dToNdInterpolation",
                                                           (boost::format("done in %1%s")% thet).str(),
                                                           this->worldComm(),this->verboseAllProc());
            }
            //---------------------------------------------//
        }
    }

    if ( this->fluid()->doRestart() )
        this->fluid()->getMeshALE()->revertMovingMesh();

    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","constructor", "finish",
                                               this->worldComm(),this->verboseAllProc());

}

//-----------------------------------------------------------------------------------//

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::buildOperatorDispStructToFluid()
{
    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","buildDispStructToFluid", "start",
                                               this->worldComm(),this->verboseAllProc());
    boost::timer btime;
    if (M_solid->isStandardModel())
    {
        this->initDispInterpolation();
    }
    else if ( M_solid->is1dReducedModel() )
    {
        this->initDisp1dToNdInterpolation();
    }
    else std::cout << "[InterpolationFSI] : BUG " << std::endl;
    std::ostringstream ostr1;ostr1<<btime.elapsed()<<"s";
    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","buildDispStructToFluid", "finish in "+ostr1.str(),
                                               this->worldComm(),this->verboseAllProc());
}

//-----------------------------------------------------------------------------------//

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::buildOperatorNormalStressFluidToStruct()
{
    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","buildOperatorNormalStressFluidToStruct", "start",
                                               this->worldComm(),this->verboseAllProc());
    boost::timer btime;
    if ( M_solid->isStandardModel() )
    {
        this->initStressInterpolation();
    }
    else if ( M_solid->is1dReducedModel() )
    {
        this->initStress1dToNdInterpolation();
    }
    else std::cout << "[InterpolationFSI] : BUG " << std::endl;
    std::ostringstream ostr1;ostr1<<btime.elapsed()<<"s";
    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","buildOperatorNormalStressFluidToStruct", "finish in "+ostr1.str(),
                                               this->worldComm(),this->verboseAllProc());
}

//-----------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------//



template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::initDispInterpolation()
{
    if (M_interfaceFSIisConforme)
    {
        if (this->verbose() && this->fluid()->worldComm().isMasterRank() )
            std::cout << "initDispInterpolation() CONFORME"  << std::endl;
        M_opDisp2dTo2dconf = opInterpolation(_domainSpace=this->solid()->functionSpaceDisplacement(),
                                             _imageSpace=this->fluid()->getMeshALE()->displacement()->functionSpace(),
                                             _range=markedfaces(this->fluid()->mesh(),this->fluid()->markersNameMovingBoundary()),
                                             _type=InterpolationConforme(),
                                             _backend=this->fluid()->backend() );
    }
    else
    {
        if (this->verbose() && this->fluid()->worldComm().isMasterRank())
            std::cout << "initDispInterpolation() NONCONFORME" << std::endl;
        M_opDisp2dTo2dnonconf = opInterpolation(_domainSpace=this->solid()->functionSpaceDisplacement(),
                                                _imageSpace=this->fluid()->getMeshALE()->displacement()->functionSpace(),
                                                _range=markedfaces(this->fluid()->mesh(),this->fluid()->markersNameMovingBoundary()),
                                                _type=InterpolationNonConforme(),
                                                _backend=this->fluid()->backend() );
    }
}


//-----------------------------------------------------------------------------------//

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::initDisp1dToNdInterpolation()
{
    if ( this->fluid()->markersNameMovingBoundary().empty() ) return;

    if (M_interfaceFSIisConforme)
    {
        if (this->verbose() && this->fluid()->worldComm().isMasterRank())
            std::cout << "initDisp1dToNdInterpolation() CONFORME"  << std::endl;
        M_opDisp1dToNdconf = opInterpolation(_domainSpace=this->solid()->fieldDisplacementVect1dReduced().functionSpace(),
                                             _imageSpace=this->fluid()->getMeshALE()->displacement()->functionSpace(),//M_fluid->meshDisplacementOnInterface().functionSpace(),
                                             _range=markedfaces(this->fluid()->mesh(),this->fluid()->markersNameMovingBoundary()),
                                             _type=InterpolationConforme(),
                                             _backend=M_fluid->backend() );
    }
    else
    {
        if (this->verbose() && this->fluid()->worldComm().isMasterRank())
            std::cout << "initDisp1dToNdInterpolation() NONCONFORME" << std::endl;
        M_opDisp1dToNdnonconf = opInterpolation(_domainSpace=this->solid()->fieldDisplacementVect1dReduced().functionSpace(),
                                                _imageSpace=this->fluid()->getMeshALE()->displacement()->functionSpace(),//M_fluid->meshDisplacementOnInterface().functionSpace(),
                                                _range=markedfaces(this->fluid()->mesh(),this->fluid()->markersNameMovingBoundary()),
                                                _type=InterpolationNonConforme(),
                                                _backend=M_fluid->backend() );
    }
}

//-----------------------------------------------------------------------------------//

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::initStressInterpolation()
{
    std::vector<int> saveActivities_stress = M_fluid->getNormalStress()->functionSpace()->worldComm().activityOnWorld();
    if (M_fluid->worldComm().globalSize()>1 && !M_fluid->functionSpace()->hasEntriesForAllSpaces() )
        M_fluid->getNormalStress()->functionSpace()->worldComm().applyActivityOnlyOn(0/*VelocityWorld*/);

    if (M_interfaceFSIisConforme)
    {
        if (this->verbose() && M_fluid->worldComm().globalRank()==M_fluid->worldComm().masterRank())
            std::cout << "initStressInterpolation() CONFORME" << std::endl;
        M_opStress2dTo2dconf = opInterpolation(_domainSpace=this->fluid()->getNormalStress()->functionSpace(),
                                               _imageSpace=this->solid()->normalStressFromFluid()->functionSpace(),
                                               _range=markedfaces(this->solid()->mesh(),this->solid()->getMarkerNameFSI()),
                                               _type=InterpolationConforme(),
                                               _backend=M_fluid->backend() );
    }
    else
    {
        if (this->verbose() && M_fluid->worldComm().globalRank()==M_fluid->worldComm().masterRank())
            std::cout << "initStressInterpolation() NONCONFORME" << std::endl;
        M_opStress2dTo2dnonconf = opInterpolation(_domainSpace=this->fluid()->getNormalStress()->functionSpace(),
                                                  _imageSpace=this->solid()->normalStressFromFluid()->functionSpace(),
                                                  _range=markedfaces(this->solid()->mesh(),this->solid()->getMarkerNameFSI()),
                                                  _type=InterpolationNonConforme(true,true,true,15),
                                                  _backend=M_fluid->backend() );
    }
    // revert initial activities
    if (M_fluid->worldComm().globalSize()>1  && !M_fluid->functionSpace()->hasEntriesForAllSpaces() )
        M_fluid->getNormalStress()->functionSpace()->worldComm().setIsActive(saveActivities_stress);
}

//-----------------------------------------------------------------------------------//

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::initStress1dToNdInterpolation()
{
    if (M_interfaceFSIisConforme)
    {
        if (this->verbose() && M_fluid->worldComm().globalRank()==M_fluid->worldComm().masterRank())
            std::cout << "initStress1dToNdInterpolation() CONFORME" << std::endl;
        M_opStress1dToNdconf = opInterpolation(_domainSpace=M_fluid->getNormalStress()->functionSpace(),
                                               _imageSpace=M_solid->getStressVect1dReduced().functionSpace(),
                                               _range=elements(M_solid->mesh1dReduced()),
                                               _type=InterpolationConforme(),
                                               _backend=M_fluid->backend() );

    }
    else
    {
        if (this->verbose() && M_fluid->worldComm().globalRank()==M_fluid->worldComm().masterRank())
            std::cout << "initStress1dToNdInterpolation() NONCONFORME" << std::endl;
        M_opStress1dToNdnonconf = opInterpolation(_domainSpace=M_fluid->getNormalStress()->functionSpace(),
                                                  _imageSpace=M_solid->getStressVect1dReduced().functionSpace(),
                                                  _range=elements(M_solid->mesh1dReduced()),
                                                  _type=InterpolationNonConforme(),
                                                  _backend=M_fluid->backend() );
    }
}

//-----------------------------------------------------------------------------------//

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::initVelocityInterpolation()
{
    if (M_interfaceFSIisConforme)
    {
        if (this->verbose() && this->fluid()->worldComm().isMasterRank())
            std::cout << "initVelocityInterpolation() CONFORME" << std::endl;
        M_opVelocity2dTo2dconf = opInterpolation(_domainSpace=this->solid()->fieldVelocity().functionSpace(),
                                                 _imageSpace=this->fluid()->meshVelocity2().functionSpace(),
                                                 _range=markedfaces(this->fluid()->mesh(),this->fluid()->markersNameMovingBoundary()),
                                                 _type=InterpolationConforme(),
                                                 _backend=this->fluid()->backend() );

    }
    else
    {
        if (this->verbose() && this->fluid()->worldComm().isMasterRank())
            std::cout << "initVelocityInterpolation() NONCONFORME" << std::endl;
        M_opVelocity2dTo2dnonconf = opInterpolation(_domainSpace=this->solid()->fieldVelocity().functionSpace(),
                                                    _imageSpace=this->fluid()->meshVelocity2().functionSpace(),
                                                    _range=markedfaces(this->fluid()->mesh(),this->fluid()->markersNameMovingBoundary()),
                                                    _type=InterpolationNonConforme(),
                                                    _backend=this->fluid()->backend() );
    }
}

//-----------------------------------------------------------------------------------//

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::initVelocity1dToNdInterpolation()
{
    if (M_interfaceFSIisConforme)
    {
        if (this->verbose() && this->fluid()->worldComm().isMasterRank())
            std::cout << "initVelocity1dToNdInterpolation() CONFORME" << std::endl;
        M_opVelocity1dToNdconf = opInterpolation(_domainSpace=this->solid()->fieldVelocityVect1dReduced().functionSpace(),
                                                 _imageSpace=this->fluid()->meshVelocity2().functionSpace(),
                                                 _range=markedfaces(this->fluid()->mesh(),this->fluid()->markersNameMovingBoundary()),
                                                 _type=InterpolationConforme(),
                                                 _backend=this->fluid()->backend() );
    }
    else
    {
        if (this->verbose() && this->fluid()->worldComm().isMasterRank())
            std::cout << "initVelocity1dToNdInterpolation() NONCONFORME" << std::endl;
        M_opVelocity1dToNdnonconf = opInterpolation(_domainSpace=this->solid()->fieldVelocityVect1dReduced().functionSpace(),
                                                    _imageSpace=this->fluid()->meshVelocity2().functionSpace(),
                                                    _range=markedfaces(this->fluid()->mesh(),this->fluid()->markersNameMovingBoundary()),
                                                    _type=InterpolationNonConforme(),
                                                    _backend=this->fluid()->backend() );
    }
}

//-----------------------------------------------------------------------------------//

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::initVelocityInterpolationF2S()
{

    if (M_interfaceFSIisConforme)
    {
        if (this->verbose() && this->fluid()->worldComm().isMasterRank())
            std::cout << "initVelocityInterpolationF2S() CONFORME" << std::endl;
        M_opVelocity2dTo2dconfF2S = opInterpolation(_domainSpace=this->fluid()->functionSpaceVelocity(),
                                                    _imageSpace=this->solid()->velocityInterfaceFromFluid()->functionSpace(),
                                                    _range=markedfaces(this->solid()->mesh(),this->solid()->getMarkerNameFSI()),
                                                    _type=InterpolationConforme(),
                                                    _backend=this->fluid()->backend() );

    }
    else
    {
#if 0
        if (this->verbose() && this->fluid()->worldComm().isMasterRank())
            std::cout << "initVelocityInterpolation() NONCONFORME" << std::endl;
        M_opVelocity2dTo2dnonconfF2S = opInterpolation(_domainSpace=this->fluid()->meshVelocity2().functionSpace(),
                                                       _imageSpace=this->solid()->fieldVelocity()->functionSpace(),
                                                       _range=markedfaces(this->solid()->mesh(),this->solid()->getMarkerNameFSI()),
                                                       _type=InterpolationNonConforme(),
                                                       _backend=this->fluid()->backend() );
#endif
    }
}

//-----------------------------------------------------------------------------------//

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::initStressInterpolationS2F()
{
    M_opStress2dTo2dconfS2F = opInterpolation(_domainSpace=this->solid()->normalStressFromStruct()->functionSpace(),
                                              _imageSpace=this->fluid()->normalStressFromStruct()->functionSpace(),
                                              _range=markedfaces(this->fluid()->mesh(),this->fluid()->markersNameMovingBoundary()),
                                              _type=InterpolationConforme(),
                                              _backend=this->fluid()->backend() );
}

//-----------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------//

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::transfertDisplacement()
{
    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","transfertDisplacement", "start",
                                               this->worldComm(),this->verboseAllProc());

    if (M_solid->isStandardModel())
    {
        if (M_interfaceFSIisConforme)
        {
            CHECK( M_opDisp2dTo2dconf ) << "interpolation operator not build";
            M_opDisp2dTo2dconf->apply(M_solid->fieldDisplacement(),
                                      *(M_fluid->meshDisplacementOnInterface()) );
        }
        else
        {
            CHECK( M_opDisp2dTo2dnonconf ) << "interpolation operator not build";
            M_opDisp2dTo2dnonconf->apply(M_solid->fieldDisplacement(),
                                         *(M_fluid->meshDisplacementOnInterface()) );
        }
    }
    else if ( M_solid->is1dReducedModel() )
    {
        M_solid->updateInterfaceDispFrom1dDisp();
        if (M_interfaceFSIisConforme)
        {
            CHECK( M_opDisp1dToNdconf ) << "interpolation operator not build";
            M_opDisp1dToNdconf->apply(M_solid->fieldDisplacementVect1dReduced(),
                                      *(M_fluid->meshDisplacementOnInterface() ) );
        }
        else
        {
            CHECK( M_opDisp1dToNdnonconf ) << "interpolation operator not build";
            M_opDisp1dToNdnonconf->apply(M_solid->fieldDisplacementVect1dReduced(),
                                         *(M_fluid->meshDisplacementOnInterface() ) );
        }
    }
    else std::cout << "[InterpolationFSI] : BUG " << std::endl;

    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","transfertDisplacement", "finish",
                                               this->worldComm(),this->verboseAllProc());
}

//-----------------------------------------------------------------------------------//

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::transfertStress()
{
    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","transfertStress", "start",
                                               this->worldComm(),this->verboseAllProc());

    M_fluid->updateNormalStress();

    std::vector<int> saveActivities_stress = M_fluid->getNormalStress()->map().worldComm().activityOnWorld();
    if (M_fluid->worldComm().globalSize()>1  && !M_fluid->functionSpace()->hasEntriesForAllSpaces()) M_fluid->getNormalStress()->map().worldComm().applyActivityOnlyOn(0/*VelocityWorld*/);

    if (M_solid->isStandardModel())
    {
        if (M_interfaceFSIisConforme)
        {
            CHECK( M_opStress2dTo2dconf ) << "interpolation operator not build";
            M_opStress2dTo2dconf->apply( *(M_fluid->getNormalStress()), *(M_solid->normalStressFromFluid()) );
        }
        else
        {
#if 1
            CHECK( M_opStress2dTo2dnonconf ) << "interpolation operator not build";
            M_opStress2dTo2dnonconf->apply( *(M_fluid->getNormalStress()), *(M_solid->normalStressFromFluid()) );
#else
            //auto FluidPhysicalName = M_fluid->getMarkerNameFSI().front();
            auto mysubmesh = createSubmesh(this->fluid()->mesh(),markedfaces(this->fluid()->mesh(),this->fluid()->markersNameMovingBoundary()/*FluidPhysicalName*/));
            typedef Mesh<Simplex<1,1,2> > mymesh_type;
            typedef bases<Lagrange<1, Vectorial,Continuous,PointSetFekete> > mybasis_stress_type;
            typedef FunctionSpace<mymesh_type, mybasis_stress_type> myspace_stress_type;
            auto myXh = myspace_stress_type::New(mysubmesh);

            typedef bases<Lagrange<1, Vectorial,Discontinuous,PointSetFekete> > mybasis_disc_stress_type;
            typedef FunctionSpace<mymesh_type, mybasis_disc_stress_type> myspace_disc_stress_type;
            auto myXhdisc = myspace_disc_stress_type::New(mysubmesh);
            auto myudisc = myXhdisc->element();

            auto myopStressConv = opInterpolation(_domainSpace=M_fluid->getNormalStress()->functionSpace(),
                                                  _imageSpace=myXhdisc,
                                                  _range=elements(mysubmesh),
                                                  _type=InterpolationConforme(),
                                                  _backend=M_fluid->backend() );

            myopStressConv->apply(*M_fluid->getNormalStress(),myudisc);


            auto opProj = opProjection(_domainSpace=myXh,
                                       _imageSpace=myXh,
                                       //_backend=backend_type::build( this->vm(), "", worldcomm ),
                                       _type=Feel::L2);//L2;
            auto proj_beta = opProj->operator()(vf::trans(vf::idv(myudisc/*M_fluid->getNormalStress()*/)));

            auto SolidPhysicalName = M_solid->getMarkerNameFSI().front();
            auto myopStress2dTo2dnonconf = opInterpolation(_domainSpace=myXh,//M_fluid->getNormalStress()->functionSpace(),
                                                           _imageSpace=M_solid->getStress()->functionSpace(),
                                                           _range=markedfaces(M_solid->mesh(),SolidPhysicalName),
                                                           _type=InterpolationNonConforme(),
                                                           _backend=M_fluid->backend() );

            myopStress2dTo2dnonconf->apply(proj_beta,*(M_solid->getStress()));
#endif
        }




    }
    else if ( M_solid->is1dReducedModel() )
    {
        if (M_interfaceFSIisConforme)
        {
            CHECK( M_opStress1dToNdconf )  << "interpolation operator not build";
            M_opStress1dToNdconf->apply(*(M_fluid->getNormalStress()), M_solid->getStressVect1dReduced() );
        }
        else
        {
            CHECK( M_opStress1dToNdnonconf )  << "interpolation operator not build";
            M_opStress1dToNdnonconf->apply(*(M_fluid->getNormalStress()), M_solid->getStressVect1dReduced() );
        }
        M_solid->updateInterfaceScalStressDispFromVectStress();
    }

    // revert initial activities
    if (M_fluid->worldComm().globalSize()>1  && !M_fluid->functionSpace()->hasEntriesForAllSpaces())
        M_fluid->getNormalStress()->map().worldComm().setIsActive(saveActivities_stress);

    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","transfertStress", "finish",
                                               this->worldComm(),this->verboseAllProc());

}

//-----------------------------------------------------------------------------------//

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::transfertVelocity()
{
    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","transfertVelocity", "start",
                                               this->worldComm(),this->verboseAllProc());

    if (M_solid->isStandardModel())
    {
        if (M_interfaceFSIisConforme)
        {
            CHECK( M_opVelocity2dTo2dconf ) << "interpolation operator not build";
            M_opVelocity2dTo2dconf->apply( M_solid->fieldVelocity(), M_fluid->meshVelocity2() );
        }
        else
        {
            CHECK( M_opVelocity2dTo2dnonconf ) << "interpolation operator not build";
            M_opVelocity2dTo2dnonconf->apply( M_solid->fieldVelocity(), M_fluid->meshVelocity2() );
        }
    }
    else if ( M_solid->is1dReducedModel() )
    {
        M_solid->updateInterfaceVelocityFrom1dVelocity();
        if (M_interfaceFSIisConforme)
        {
            CHECK( M_opVelocity1dToNdconf ) << "interpolation operator not build";
            M_opVelocity1dToNdconf->apply(M_solid->fieldVelocityVect1dReduced(),
                                          M_fluid->meshVelocity2() );
        }
        else
        {
            CHECK( M_opVelocity1dToNdnonconf ) << "interpolation operator not build";
            M_opVelocity1dToNdnonconf->apply(M_solid->fieldVelocityVect1dReduced(),
                                             M_fluid->meshVelocity2() );
        }
    }

    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","transfertVelocity", "finish",
                                               this->worldComm(),this->verboseAllProc());
}

//-----------------------------------------------------------------------------------//

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::transfertStressS2F()
{
    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","transfertStressS2F", "start",
                                               this->worldComm(),this->verboseAllProc());

    this->solid()->updateNormalStressFromStruct();
    CHECK( M_opStress2dTo2dconfS2F ) << "interpolation operator not build";
    M_opStress2dTo2dconfS2F->apply(*this->solid()->normalStressFromStruct(),
                                   *this->fluid()->normalStressFromStruct());

    if (this->verbose()) Feel::FeelModels::Log("InterpolationFSI","transfertStressS2F", "finish",
                                               this->worldComm(),this->verboseAllProc());
}

template< class FluidType, class SolidType >
void
InterpolationFSI<FluidType,SolidType>::transfertVelocityF2S(bool useExtrapolation)
{
    if ( useExtrapolation )
    {
        if (false)
        {
            // bdf extrapolation
            auto solExtrap = this->fluid()->timeStepBDF()->polyDeriv();
            auto velExtrap = solExtrap.template element<0>();
            if (M_interfaceFSIisConforme)
            {
                CHECK( M_opVelocity2dTo2dconfF2S ) << "interpolation operator not build";
                M_opVelocity2dTo2dconfF2S->apply( velExtrap,*this->solid()->velocityInterfaceFromFluid() );
            }
            else
            {
                CHECK(false) << "TODO\n";
            }
        }
        else
        {
            // extrap in Explicit strategies for incompressible fluid-structure interaction problems: Nitche ....
#if 0
            auto velExtrap = this->fluid()->functionSpace()->template functionSpace<0>()->element();
            velExtrap.add(  2.0, this->fluid()->getSolution()->template element<0>() );
            velExtrap.add( -1.0, this->fluid()->timeStepBDF()->unknown(0).template element<0>() );
#else
            auto velExtrap = this->fluid()->functionSpace()->template functionSpace<0>()->element();
            velExtrap.add(  2.0, this->fluid()->timeStepBDF()->unknown(0).template element<0>() );
            velExtrap.add( -1.0, this->fluid()->timeStepBDF()->unknown(1).template element<0>() );
#endif
            if (M_interfaceFSIisConforme)
            {
                CHECK( M_opVelocity2dTo2dconfF2S ) << "interpolation operator not build";
                M_opVelocity2dTo2dconfF2S->apply( velExtrap,*this->solid()->velocityInterfaceFromFluid() );
            }
            else
            {
                CHECK(false) << "TODO\n";
            }
        }
    }
    else // no extrap : take current solution
    {
        if (M_interfaceFSIisConforme)
        {
            CHECK( M_opVelocity2dTo2dconfF2S ) << "interpolation operator not build";
            M_opVelocity2dTo2dconfF2S->apply( this->fluid()->timeStepBDF()->unknown(0).template element<0>(),//this->fluid()->getSolution()->template element<0>(),
                                              *this->solid()->velocityInterfaceFromFluid() );
        }
        else
        {
            CHECK(false) << "TODO\n";
        }
    }
}



} // namespace FeelModels
} // namespace Feel