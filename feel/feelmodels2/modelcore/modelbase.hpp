/* -*- mode: c++; coding: utf-8; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; show-trailing-whitespace: t -*- vim:fenc=utf-8:ft=tcl:et:sw=4:ts=4:sts=4

 This file is part of the Feel library

 Author(s): Vincent Chabannes <vincent.chabannes@feelpp.org>
 Date: 2012-01-19

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
 \file modelbase.hpp
 \author Vincent Chabannes <vincent.chabannes@feelpp.org>
 \date 2012-01-19
 */

#ifndef FEELPP_MODELBASE_HPP
#define FEELPP_MODELBASE_HPP 1

#include <feel/options.hpp>
#include <feel/feelcore/environment.hpp>
#include <feel/feelcore/pslogger.hpp>
#include <feel/feelcore/worldcomm.hpp>

#include <feel/feelmodels2/modelcore/feelmodelscoreconstconfig.h>
#include <feel/feelmodels2/modelcore/log.hpp>
#include <feel/feelmodels2/modelcore/timertool.hpp>


namespace Feel
{
namespace FeelModels
{


class ModelBase
{
public :
    ModelBase( std::string _theprefix,
               WorldComm const& _worldComm=Environment::worldComm(),
               std::string subPrefix="",
               std::string appliShortRepository=soption(_name="exporter.directory") );

    ModelBase( ModelBase const& app ) = default;
    virtual ~ModelBase();

    // worldcomm
    WorldComm const& worldComm() const;
    std::vector<WorldComm> const& worldsComm() const;
    void setWorldsComm(std::vector<WorldComm> const& _worldsComm);
    std::vector<WorldComm> const& localNonCompositeWorldsComm() const;
    void setLocalNonCompositeWorldsComm(std::vector<WorldComm> const& _worldsComm);
    virtual void createWorldsComm();
    // prefix
    std::string prefix() const;
    std::string subPrefix() const;
    // vm
    po::variables_map const& vm() const;
    // appli repository
    std::string appliRepositoryWithoutNumProc() const;
    std::string appliRepository() const;
    std::string appliShortRepository() const;
    std::string appliShortRepositoryWithNumProc() const;
    // verbose
    bool verbose() const;
    bool verboseAllProc() const;
    void log( std::string _className,std::string _functionName,std::string _msg ) const;
    // info
    std::string filenameSaveInfo() const;
    void setFilenameSaveInfo(std::string s);
    virtual boost::shared_ptr<std::ostringstream> getInfo() const;
    virtual void printInfo() const;
    virtual void saveInfo() const;
    virtual void printAndSaveInfo() const;
    // timer
    TimerToolBase & timerTool(std::string s) const;
    void addTimerTool(std::string s,std::string fileName) const;
    // save assembly/solver scalability
    bool scalabilitySave() const;
    bool scalabilityReinitSaveFile() const;
    void setScalabilitySave( bool b );
    std::string scalabilityPath() const;
    void setScalabilityPath(std::string s);
    std::string scalabilityFilename() const;
    void setScalabilityFilename(std::string s);

private :
    // worldcomm
    WorldComm M_worldComm;
    std::vector<WorldComm> M_worldsComm;
    std::vector<WorldComm> M_localNonCompositeWorldsComm;
    // prefix
    std::string M_prefix;
    std::string M_subPrefix;
    // short repository name
    std::string M_appliShortRepository;
    // verbose
    bool M_verbose,M_verboseAllProc;
    // filename for save info
    std::string M_filenameSaveInfo;
    // timertool register by a name id
    mutable std::map<std::string,std::shared_ptr<TimerToolBase> > M_mapTimerTool;
    bool M_timersActivated;
    bool M_timersSaveFileMasterRank, M_timersSaveFileMax, M_timersSaveFileMin, M_timersSaveFileMean, M_timersSaveFileAll;
    // save assembly/solver scalability
    bool M_scalabilitySave, M_scalabilityReinitSaveFile;
    std::string M_scalabilityPath;
    std::string M_scalabilityFilename;
};

// null application
struct ModelBaseNull
{
    static const bool is_class_null = true;
};


} // namespace FeelModels
} // namespace feel


#endif //endif FEELPP_MODELBASE_HPP