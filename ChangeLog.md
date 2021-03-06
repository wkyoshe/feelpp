ChangeLog {#ChangeLog}
======================

[TOC]

# Feel++ Release 0.100.0 {#feelpp01000}
release date dd-mm-2014

## Features

   - Support Block preconditioning for Navier-Stokes (PMM and PCD)
   - A lot of various fixes for the exporters: EnsightGold, HDF5
   - Support for many configuration files that can be combined (e.g. to change
     automatically solver strategies)
   - Start work on boundary conditions generic framework, see examples in quickstart

##  Noteworthy Issues ##

   - FTBS inner keyword when using terminal keyword [Issue <a href="https://github.com/feelpp/feelpp/issues/577">577</a>]
   - Support more features in the ginac parser [Issue <a href="https://github.com/feelpp/feelpp/issues/568">568</a>]
   - Feature/edge [Issue <a href="https://github.com/feelpp/feelpp/pull/557">557</a>]
   - Add support for modulo [Issue <a href="https://github.com/feelpp/feelpp/issues/549">549</a>]
   - Add support for casting expressions from one type to another in the language [Issue <a href="https://github.com/feelpp/feelpp/issues/548">548</a>]
   - Add support for floor and ceil in language [Issue <a href="https://github.com/feelpp/feelpp/issues/546">546</a>]
   - Bug in handling face dof in vectorial finite elements (e.g. Nedelec,RT) [Issue <a href="https://github.com/feelpp/feelpp/issues/544">544</a>]
   - Support interpolation and dirichlet conditions based on range of edges and points [Issue <a href="https://github.com/feelpp/feelpp/issues/537">537</a>]
   - Support Matrix fields  [Issue <a href="https://github.com/feelpp/feelpp/issues/535">535</a>]
   - Add support for component-wise dirichlet condition in vector fields [Issue <a href="https://github.com/feelpp/feelpp/issues/534">534</a>]
   - eigenPair : each call erase previous eigen functions  [Issue <a href="https://github.com/feelpp/feelpp/issues/533">533</a>]
   - Support pointwise operations in Vector<> [Issue <a href="https://github.com/feelpp/feelpp/issues/509">509</a>]
   - Customize PETSc/KSP monitors [Issue <a href="https://github.com/feelpp/feelpp/issues/503">503</a>]
   - printMatlab : The script should not have the same name than the variable [Issue <a href="https://github.com/feelpp/feelpp/issues/501">501</a>]
   - Add support for -mat_mumps_icntl_7  [Issue <a href="https://github.com/feelpp/feelpp/issues/499">499</a>]
   - FTE in feelpp_test_integration_relatedmesh  [Issue <a href="https://github.com/feelpp/feelpp/issues/498">498</a>]
   - Feature/faster  [Issue <a href="https://github.com/feelpp/feelpp/pull/497">497</a>]
   - Support Schur complement Pressure Mass Matrix for Stokes [Issue <a href="https://github.com/feelpp/feelpp/issues/495">495</a>]
   - Optimize and cleanup DofTable [Issue <a href="https://github.com/feelpp/feelpp/issues/490">490</a>]
   - Reduce compilation cost in creategmshmesh [Issue <a href="https://github.com/feelpp/feelpp/issues/488">488</a>]
   - Configure Aitken tool from command line options [Issue <a href="https://github.com/feelpp/feelpp/issues/483">483</a>]
   - Support map of ginac expression [Issue <a href="https://github.com/feelpp/feelpp/issues/482">482</a>]
   - Port on MAC OS Yosemite [Issue <a href="https://github.com/feelpp/feelpp/issues/466">466</a>]
   - OpenMP not usable [Issue <a href="https://github.com/feelpp/feelpp/issues/464">464</a>]
   - Operator Framework (#457) [Issue <a href="https://github.com/feelpp/feelpp/pull/458">458</a>]
   - Support Operator framework  [Issue <a href="https://github.com/feelpp/feelpp/issues/457">457</a>]
   - Support interprocessedges mesh filter [Issue <a href="https://github.com/feelpp/feelpp/issues/454">454</a>]
   - Class Mesh  [Issue <a href="https://github.com/feelpp/feelpp/issues/453">453</a>]
   - Support atan2 keyword in language [Issue <a href="https://github.com/feelpp/feelpp/issues/450">450</a>]
   - FTE test_mortar  [Issue <a href="https://github.com/feelpp/feelpp/issues/449">449</a>]
   

## Platform specific

   - Support for Debian and Ubuntu (12.04, 14.04 and 14.10)
   - Support for Prace supercomputer Curie@TGCC (France)
   - Support for Mesocenters Grenoble and Strasbourg
   - Support for MacOSX homebrew and macport including Yosemite

# Feel++ Release 0.99.0 {#feelpp0990}
   release date 07-09-2014

## Changes

   - Improve documentation, see <a
     href="https://github.com/feelpp/feelpp/issues/300">#300</a>
   - Refactoring of the linear and nonlinears solver and preconditioner framework

## Features

   - Support CMake 3.0
   - Support Boost from 1.49 to 1.56
   - Support PETSc from 3.1 to 3.5.1
   - Support SLEPc from 3.1 to 3.5
   - Support GCC from 4.7 to 4.9 (g++ versions that support the c++11 standard)
   - Support CLANG from 3.2 to 3.5
   - Support INTEL C++ Compiler starting from intel.15 version
   - Support INTEL MKL starting from version 11
   - Support in-memory on Gmsh data structures (Geo and Msh) see <a href="https://github.com/feelpp/feelpp/issues/412">#295</a>
   - Support NLOpt see <a href="https://github.com/feelpp/feelpp/issues/407">#407</a>
   - Started work on Python wrapper thanks to internship of T. Lantz, see <a href="https://github.com/feelpp/feelpp/issues/366">#366</a>
   - New XDMF/HDF5 exporter thanks to internship of B. Vanthong, see <a href="https://github.com/feelpp/feelpp/issues/194">#194</a>

## Noteworthy Issues

   - Support more continuous integration using Travis [Issue <a href="https://github.com/feelpp/feelpp/issues/436">436</a>]
   - Enable support for simd  [Issue <a href="https://github.com/feelpp/feelpp/issues/435">435</a>]
   - MPIIO integer size detection breaks feel++ 32 bits platforms [Issue <a href="https://github.com/feelpp/feelpp/issues/434">434</a>]
   - FindXdmf.cmake missing [Issue <a href="https://github.com/feelpp/feelpp/issues/433">433</a>]
   - Add backend as argument to form1 and form2 [Issue <a href="https://github.com/feelpp/feelpp/issues/431">431</a>]
   - Add support for set of elements of function spaces [Issue <a href="https://github.com/feelpp/feelpp/issues/430">430</a>]
   - Add support for Matrix transpose without assembly [Issue <a href="https://github.com/feelpp/feelpp/issues/427">427</a>]
   - Add support for newMatrix() without args [Issue <a href="https://github.com/feelpp/feelpp/issues/426">426</a>]
   - Add compatibility headers in contrib/gmsh depending on version [Issue <a href="https://github.com/feelpp/feelpp/issues/425">425</a>]
   - Add Eigen3 3.2.2 to contrib [Issue <a href="https://github.com/feelpp/feelpp/issues/422">422</a>]
   - Better support ML with cmake [Issue <a href="https://github.com/feelpp/feelpp/issues/421">421</a>]
   - Support MKL (starting from v11) [Issue <a href="https://github.com/feelpp/feelpp/issues/420">420</a>]
   - Support boost 1.56 [Issue <a href="https://github.com/feelpp/feelpp/issues/419">419</a>]
   - Add functionality to check/test Feel++ version [Issue <a href="https://github.com/feelpp/feelpp/issues/418">418</a>]
   - Add application to provide various mesh information [Issue <a href="https://github.com/feelpp/feelpp/issues/417">417</a>]
   - Support PETSc 3.5.X and above [Issue <a href="https://github.com/feelpp/feelpp/issues/415">415</a>]
   - Support SLEPc 3.4.X and above [Issue <a href="https://github.com/feelpp/feelpp/issues/414">414</a>]
   - Set processor affinity & dump cpu information [Issue <a href="https://github.com/feelpp/feelpp/issues/413">413</a>]
   - Support Reading Gmsh data structures directly in memory [Issue <a href="https://github.com/feelpp/feelpp/issues/412">412</a>]
   - Port to cmake 3.0 [Issue <a href="https://github.com/feelpp/feelpp/issues/411">411</a>]
   - Add an option to enable/disable creation of the np_<nproc> subdirectory [Issue <a href="https://github.com/feelpp/feelpp/issues/410">410</a>]
   - problem with markerToDof function  [Issue <a href="https://github.com/feelpp/feelpp/issues/409">409</a>]
   - Bug in graph construction: more non zero entries in rows than there are entries [Issue <a href="https://github.com/feelpp/feelpp/issues/408">408</a>]
   - Add support for (non-linear) optimisation libraries [Issue <a href="https://github.com/feelpp/feelpp/issues/407">407</a>]
   - Need to access to the neighbours of dof and to change value of functions only on some dof [Issue <a href="https://github.com/feelpp/feelpp/issues/404">404</a>]
   - Exporter Ensight not work [Issue <a href="https://github.com/feelpp/feelpp/issues/403">403</a>]
   - Problem with feelpp_doc_traces [Issue <a href="https://github.com/feelpp/feelpp/issues/401">401</a>]
   - Fast Marching with Hypercube [Issue <a href="https://github.com/feelpp/feelpp/issues/399">399</a>]
   - .geo parser [Issue <a href="https://github.com/feelpp/feelpp/issues/398">398</a>]
   - Support variable expansion in options [Issue <a href="https://github.com/feelpp/feelpp/issues/391">391</a>]
   - Non existing marked elements [Issue <a href="https://github.com/feelpp/feelpp/issues/389">389</a>]
   - Unregistered options [Issue <a href="https://github.com/feelpp/feelpp/issues/385">385</a>]
   - Random ensight case file generation depending on architecture [Issue <a href="https://github.com/feelpp/feelpp/issues/379">379</a>]
   - Provide average, min and max mesh size [Issue <a href="https://github.com/feelpp/feelpp/issues/377">377</a>]
   - Bug in initialisation of CRBModel in composite case [Issue <a href="https://github.com/feelpp/feelpp/issues/361">361</a>]
   - Bug in non conforming interpolation when space are the same but the mesh is not [Issue <a href="https://github.com/feelpp/feelpp/issues/356">356</a>]
   - Bug in mortar dof table points coordinates [Issue <a href="https://github.com/feelpp/feelpp/issues/355">355</a>]
   - Bug in one of the tests in 3D in test_integration_opt (high order geom) [Issue <a href="https://github.com/feelpp/feelpp/issues/354">354</a>]

## Platform specific

   - MACOSX: when using cmake3 set MACOS_RPATH to ON by default
   - MACOSX: when using cmake3 set CMAKE_INSTALL_RPATH to CMAKE_INSTALL_PREFIX/lib
   - Port on Curie (@TGCC,France)

# Feel++ Release 0.98.0 {#feelpp0980}
   release date 22-05-2014


  - #374 Move test_bdf* to testsuite/feelts
  - #372 FTE in test_bdf2 : invalid c++ code generated at runtime by ginac
  - #373 Support simple operators + - in GiNaC::matrix
  - #354 Bug in one of the tests in 3D in test_integration_opt (high order geom)

## Changes

   - Improve documentation, see <a
     href="https://github.com/feelpp/feelpp/issues/300">#300</a>
   - Refactoring of the linear and nonlinears solver and preconditioner framework
   - Simplified CRB model interface

## Features

   - Support evaluating expressions over faces (not only elements) and compute
     min, max (`minmax`) and L infinity norm (`normLinf`) of these expressions
   - Support PETSc and SLEPc 3.4.4
   - Support GCC from 4.7 to 4.9 (g++ versions that support the c++11 standard)
   - Port on Froggy at Mesocentre Ciment (Grenoble,France)
   - Improve support for eim in CRB by including eim approximation error into crb
   - <a href="https://github.com/feelpp/feelpp/issues/295">#295</a> Support Gmsh export in parallel
   - <a href="https://github.com/feelpp/feelpp/issues/348">#348</a> Support evaluate of expression over faces

##  Noteworthy Issues

   - <a href="https://github.com/feelpp/feelpp/issues/356">#356</a> Bug in non conforming interpolation when space are the same but the mesh is not the same
   - <a href="https://github.com/feelpp/feelpp/issues/355">#355</a> Bug in mortar dof table points coordinates
   - <a href="https://github.com/feelpp/feelpp/issues/349">#349</a> Bug in composite spaces when subspaces are the same
   - <a href="https://github.com/feelpp/feelpp/issues/244">#244</a> Bug in test_interpolation and possibly pointwise interpolation
   - <a href="https://github.com/feelpp/feelpp/issues/350">#350</a> Set timeout for tests and application when used in ctest
   - <a href="https://github.com/feelpp/feelpp/issues/335">#335</a> Petsc Error in nlsolve
   - <a href="https://github.com/feelpp/feelpp/issues/346">#346</a> Support reading partitioned mesh on one processor
   - <a href="https://github.com/feelpp/feelpp/issues/343">#343</a> Port to gcc 4.9
   - <a href="https://github.com/feelpp/feelpp/issues/341">#341</a> Petsc error with solvereigen
   - <a href="https://github.com/feelpp/feelpp/issues/340">#340</a> Error with cross product
   - <a href="https://github.com/feelpp/feelpp/issues/339">#339</a> Error norm for CRB models using EIM
   - <a href="https://github.com/feelpp/feelpp/issues/338">#338</a> Unable to compile (at least with gcc >= 4.7)
   - <a href="https://github.com/feelpp/feelpp/issues/336">#336</a> For install feel++ on Ubuntu 12.04
   - <a href="https://github.com/feelpp/feelpp/issues/337">#337</a> Scotch5 and HomeBrew
   - <a href="https://github.com/feelpp/feelpp/issues/334">#334</a> marker are not preserved by operatorLagrangeP1

<hr>

# Feel++ Release 0.97.4 {#feelpp0974}
   release date 03-18-2014

## Changes since 0.97.3

   - Make sure that all headers are installed properly, see <a
     href="https://github.com/feelpp/feelpp/issues/318">#318</a>

#  Feel++ Release 0.97.3
   release date 03-17-2014

##  Changes since 0.97.2

   - Fix Feel++ programming environment and cmake script, see <a
     href="https://github.com/feelpp/feelpp/issues/314">#314</a>
   - Install CRB framework properly, see <a
     href="https://github.com/feelpp/feelpp/issues/315">#315</a>

#  Feel++ Release 0.97.2 {#feelpp0972}
   release date 03-16-2014

## changes0972 Changes since 0.97.1

   - Fix Feel++ programming environment and cmake script, see <a
     href="https://github.com/feelpp/feelpp/issues/314">#314</a>
   - Install simple c++ examples (laplacian, stokes, ...) with their associated
     data (config file, mesh, geometry, ...) , see <a
     href="https://github.com/feelpp/feelpp/issues/311">#311</a>

# feelpp0971 Feel++ Release 0.97.1
   release date 03-16-2014

## changes0971 Changes since 0.97.0

   - Fix support for PETSc 3.4.4, see <a
     href="https://github.com/feelpp/feelpp/issues/311">#311</a>
   - Fix installation of missing headers in 0.97.0, see <a
     href="https://github.com/feelpp/feelpp/issues/312">#312</a>
   - Master branch is now supported in our continuous integration process, see
     <a href="https://github.com/feelpp/feelpp/issues/274">#274</a>

# feelpp0970 Feel++ Release 0.97.0
   release date 03-14-2014

## changes0970 Changes

   - Improve documentation, see <a
     href="https://github.com/feelpp/feelpp/issues/300">#300</a>
   - Massive reorganisation of headers and files
   - Propose an alternative handling of header file: rather than having
     everything in one header file, include only the necessary header files
     which reduce compilation times
   - Feel++ now uses <a href="http://www.travis-ci.org">Travis-CI</a> for
     Continuous Integration, see <a
     href="http://www.travis-ci.org/feelpp/feelpp">here</a> the Feel++ status
   - Feel++ is now on Youtube: our videos are uploaded <a href="http://www.youtube.com/channel/UCnLX6kyV8j644isqhMpUN4Q/">here</a>
   - Feel++ is now on Twitter: it shows the github development activity as well
     as the Feel++ YouTube channel updates. Check it <a href="http://www.twitter.com/feelpp/">here</a>

## features0970 Features

   - Support Eigen3 to latest stable release 3.2.1
   - Support <a href="http://onelab.info/">OneLab</a> which enables a graphical
     interface through Gmsh, see <a href="https://github.com/feelpp/feelpp/issues/64">#64</a>
   - Support for discontinuous galerkin as well as internal face
     integration in parallel (1D, 2D and 3D)
   - Support discontinuous integration over a range of element (a subset of
     faces), see <a href="https://github.com/feelpp/feelpp/issues/227">#227</a>
   - Support ghost cells in ensightgold format for better visualisation (without
     artefacts between subdomain in 3D), see #243
   - Support mortar function spaces, see <a
     href="https://github.com/feelpp/feelpp/issues/36">#36</a>
   - Support the empirical interpolation method, see <a
     href="https://github.com/feelpp/feelpp/issues/26">#26</a>
   - Support initialization of element of function space with an expression, see <a
     href="https://github.com/feelpp/feelpp/issues/282">#282</a>
   - Support keyword to compute the projector to the tangent hyperplan, see <a
     href="https://github.com/feelpp/feelpp/issues/222">#222</a>
   - Support keyword to compute the norm2, see <a
     href="https://github.com/feelpp/feelpp/issues/223">#223</a>
   - Support keyword on() in element of function spaces, see <a
     href="https://github.com/feelpp/feelpp/issues/213">#213</a>
   - Simplified help messages, see <a
     href="https://github.com/feelpp/feelpp/issues/273">#273</a>


## issues0970 Noteworthy Issues
   - <a href="https://github.com/feelpp/feelpp/issues/309">#309</a> Add support for isMasterRank() in Environment
   - <a href="https://github.com/feelpp/feelpp/issues/308">#308</a> Support Ginac expression evaluation
   - <a href="https://github.com/feelpp/feelpp/issues/271">#271</a>  Assertion failure in local/global assembly using eigen fixed matrices in 3D p >= 4
   - <a href="https://github.com/feelpp/feelpp/issues/198">#198</a> FEELPP_ENABLE_MPI_MODE=OFF code branches are unmaintained and are removed
   - <a href="https://github.com/feelpp/feelpp/issues/219">#219</a> Create configure script to generate configuration for cmake
   - <a href="https://github.com/feelpp/feelpp/issues/224">#224</a> Define an integer type for mpi rank processes
   - <a href="https://github.com/feelpp/feelpp/issues/260">#260</a> Improved support for string Dirichlet condition handling

<hr>
# feelpp0960 Feel++ Release 0.96.0
   release date 01-02-2014

## changes0960 Changes

   - performance improvements in parallel computing: reduce collective
     operations, rewrite of some internals
   - improved Ginac(symbolic calculus) support
   - updated documentation to reflect Homebrew(MacOSX) support and the more
     stringent requirements on the compilers that g++ must be at least 4.6 and
     clang 3.2

## features0960 Features

   - Feel++ is now fully supported on Mac OS X systems >= 10.9 (Mavericks) using
     Homebrew and MacPorts
   - Feel++ supports creating sequential function spaces out of parallel meshes
   - Feel++ supports creating local interpolation operators in subdomains
   - Feel++ provides an implementation of the empirical interpolation method (eim)
   - Feel++ provides a new reduced basis framework that uses the eim as a
     central ingredient to obtain an affine decomposition

## issues0960 Noteworthy Issues

   - <a href="https://github.com/feelpp/feelpp/issues/202">#202</a> Intermittent
     crash when creating OperatorInterpolation
   - <a href="https://github.com/feelpp/feelpp/issues/201">#201</a> Crash when
     creating a sequential functionspace using a parallel mesh
   - <a href="https://github.com/feelpp/feelpp/issues/195">#195</a> Crash in
     DofTable (see sequential functionspace with parallel mesh feature)

# feelpp0950 Feel++ Release 0.95.0
   release date 04-10-2013

## changes0950 Changes

   - reduce tremendously the memory footprint in parallel application especially for large meshes
   - number of files generated by Ginac in parallel applications, now only one .so is generated for each expression
   - various valgrind invalid read and write fixed
   - fix memory leak using PETSc when solver/preconditioner needed frequent updates

## features0950 Features

   - support up to PETSc 3.4.2
   - support up to SLEPc 3.4.2
   - support up to Boost 1.54
   - support up to Eigen 3.2
   - Correspondence table between gmsh and feel++ node numbering allowing to
     easily couple different codes for example a feel++ code and a matlab code
   - now the boundary elements set correspond to all elements sharing a
     sub-entity with the boundary (point edge or face ) and not only a face
     this affects \c boundaryelements and \c internalelements
   - Extend support for Lambda expressions in the variational formulation
     language, now more complex expressions are allowed with the lambda
     expression framework
   - Submeshes of elements and faces can be extracted now in parallel. For
     efficient localization/interpolation later, the relation with the parent
     mesh can be kept. This is completely done under the hood.
   - Support for basic memory logging from PETSc
   - Lots of simplified user interface changes all over the place with control
     enabled from the .cfg files

## issues0950 Noteworthy Issues

   - <a href="https://github.com/feelpp/feelpp/issues/158">#157</a> Extend support for Lambda expressions
   - <a href="https://github.com/feelpp/feelpp/issues/157">#157</a> Do not ship eigen, cln, glog and gflags when releasing Feel++
   - <a href="https://github.com/feelpp/feelpp/issues/156">#156</a> extend boundary elements to all elements sharing a sub-entity with the boundary
   - <a href="https://github.com/feelpp/feelpp/issues/140">#140</a> Mesh files refined twice the number of refinement levels at generation step
   - <a href="https://github.com/feelpp/feelpp/issues/128">#128</a> BDF not working in order 4
   - <a href="https://github.com/feelpp/feelpp/issues/126">#126</a> don't store all mesh points
   - <a href="https://github.com/feelpp/feelpp/issues/102">#102</a> Clear temporary Ginac generated files when Feel++ is finalized
   - <a href="https://github.com/feelpp/feelpp/issues/101">#101</a> Correspondence of gmsh and feel++ node numbering
   - <a href="https://github.com/feelpp/feelpp/issues/58">#58</a> use comp(X) in parallel
   - <a href="https://github.com/feelpp/feelpp/issues/33">#33</a> problem with gradient of fonction real dim= Dim and topological dim=Dim-1
   - <a href="https://github.com/feelpp/feelpp/issues/13">#13</a> trace or createSubmesh in parallel

# feelpp0930 Feel++ Release 0.93.0
   release date xx-yy-2013


## changes0930 Changes

   - Feel++ is now hosted on GitHub : https://github.com/feelpp/feelpp
   - port to LRZ/SuperMUC thanks to PRACE 6th-call and HP-FEEL++ project
   - port to Strasbourg and Grenoble Mesocenters
   - major update of the feel++ online manual using Doxygen
   see [Feel++ Online Document](http://feelpp.github.io/feelpp/)


## features0930 Features

   - retrieving command line/config options
   \code
   option(_name="",_prefix="",_sub="").as<xxx>()
   // for example retrieve the option gmsh.hsize
   option(_name="gmsh.hsize").as<double>()
   \endcode
   - \c Environment::findFile(std::string) : look for a file in the list of
     directories known to Feel++ (current directory, previous directories stored
     via \c changeRepository(), and for .geo/.mshg files also \c localGeoRepository()
     and \c systemGeoRepository()
   - support for Boost 1.53
   - support for PETSc 3.4
   - support for loadleveler, slurm and ccc: automatic generation of scheduling scripts
   - new feel++ snes options
     - snes-{r,a,s}tol
     - snes-maxit
     - snes-ksp-rtol
     - ksp-maxit
     - ksp-{a,d}tol
   - Nonlinear solves with lambda function, see \ref bratu.cpp and \ref nonlinearpow.cpp
   - added \ref LoadMesh function that can load either a .geo or a .msh file
   see \ref StokesTutorial
   - support for Gmsh mesh file binary format use \c --gmsh.format=1 (binary)
   - in bi/linear forms,
     - no need for specifying the algebraic representation for bi/linear forms anymore
     \code
     auto a = form2( Xh, Xh ); auto l=form1(Xh)
     a.solve( _solution=u, _rhs=l);
     \endcode
     - support for +=
     \code
     auto a = form2( Xh, Xh ), at = form2( Xh, Xh); a += at (sum matrices)
     auto l = form1( Xh ), lt = form1( Xh ); l += lt (sum vectors)
     \endcode
     useful for example for time dependent and time independent terms handling.
   - The language now supports the following \ref Keywords
     - \c cross(u,v) (cross product)
     - \c eye<m,n>(), \c Id<m,n>() identity matrix (if non square, 1 on main diagonal, 0 elsewhere)
     - \c constant<m,n>(value) constant matrix with entries set to  "value"
     - \c zero<m,n>() matrix of zeros
     - \c inv() and \ det(): inverse and determinant, e.g. for change of variable (see \ref laplacian_polar.cpp)
     - \c sym(A) and \c antisym(A)
   - In exporters,
     - support for static, change_coords_only, remesh \ref ExporterGeometry
     - Ensight Gold support
       - support filesets
       - support scalars
       - support for markedfaces (mesh and fields)
     - options (with prefix)
       - \c exporter.format = ensight, ensightgold, gmsh
       - \c exporter.geo = 0 (static), 1(change_coords_only), 2(remesh)





## issues0930 Issues

   - <a href="https://github.com/feelpp/feelpp/issues/123">#123</a> test_ginac fails to compile
   - <a href="https://github.com/feelpp/feelpp/issues/122">#122</a> Automatic generation of API documentation from research
   - <a href="https://github.com/feelpp/feelpp/issues/121">#121</a> code in doc/manual/heatns fail to compile
   - <a href="https://github.com/feelpp/feelpp/issues/120">#120</a> Codes in doc/manual/dd fail to compile
   - <a href="https://github.com/feelpp/feelpp/issues/119">#119</a> exporter ensightgold with vectorial field
   - <a href="https://github.com/feelpp/feelpp/issues/118">#118</a> problem using -idv(...) in expression and operator linear free
   - <a href="https://github.com/feelpp/feelpp/issues/116">#116</a> Support Ensight Gold format
   - <a href="https://github.com/feelpp/feelpp/issues/111">#111</a> Compilation error of CRB models in develop branch
   - <a href="https://github.com/feelpp/feelpp/issues/109">#109</a> Load Gmsh supported file format seamlessly
   - <a href="https://github.com/feelpp/feelpp/issues/106">#106</a> Improve website documentation
   - <a href="https://github.com/feelpp/feelpp/issues/103">#103</a> Off by one error in mesh point indices
   - <a href="https://github.com/feelpp/feelpp/issues/15">#15</a> Reorder dof with respect to interior, face, edge and vertex dof of the domain
   - <a href="https://github.com/feelpp/feelpp/issues/38">#38</a> support for gmsh binary format enhancement
   - <a href="https://github.com/feelpp/feelpp/issues/45">#45</a> problem with dot function in parallel when using vectors
   - <a href="https://github.com/feelpp/feelpp/issues/56">#56</a> use multVector directly with element_type
   - <a href="https://github.com/feelpp/feelpp/issues/79">#79</a> improve export when same mesh reused enhancement
   - <a href="https://github.com/feelpp/feelpp/issues/91">#91</a> GFlags not used
   - <a href="https://github.com/feelpp/feelpp/issues/95">#95</a> Port Feel++ on SUPERMUC
   - <a href="https://github.com/feelpp/feelpp/issues/99">#99</a> (Re)Moving libmatheval Usability Component-Progenv

# feelpp0920 Feel++ Release 0.92.0

## changes0920 Changes

   - support for Boost 1.49, 1.50, 1.51 and 1.52
   - imported for Eigen 3.1 in contrib/eigen
   - port to gcc4.7, clang 3.1 and clang 3.2
   - added cmake macro feelpp_add application, see http://code.google.com/p/feelpp/issues/detail?id=11&can=1
   - support Gmsh from both executable and library(preferred and more powerful)
   - support for PETSc 3.3
   - port to Marseille mesocenter supercomputer (thx to CEMRACS'12)
   - port on the TGCC
   - added scotch Portfile from macport and use esmumps variant for mumps support
   - added PETSc 3.3-p1 support and use suitesparse as well as scotch directly
   from macport instead of downloading/compiling them
   - improved benchmarking framework and in particular the handling of the
   statistics provided by the benchmark with views per key and flat views. In
   the last case various files are automatically generated for each benchmark
   - added eigen(3.1) backend with support for dense and sparse eigen matrices
   Fixes issue #36
   - added 2D and 3D mesh adaptation using Gmsh
   - seamless parallelisation of the FunctionSpace data structure in the case of
   product of function spaces
   - lift operator merged with projection operator
   - support for mesh generation directly from Gmsh library
   - support for element splitting (Fixes issue #40)
   - many new keywords
     - mean value of a function: mean(_range=elements(mesh),_expr=sin(pi Px()));
     - norm L_2 of a function: normL2(_range=elements(mesh),_expr=sin(pi Px()));
     - norm L_2 of a function squared: normL2Squared(_range=elements(mesh),_expr=sin(pi Px()));
     - infinity norm of a function: normLinf(_range=elements(mesh),_expr=sin(pi Px()));
     - inner(a,b): a . b
     - cross(a,b): a x b
     - sym(a): .5 (a + aT )
     - zero<m,n>(): matrix of zeros of size m x n
     - ones<m,n>(): matrix of ones of size m x n
     - constant<m,n>(a): matrix of constant value a of size m x n
     - eye<m,n>(), Id<m,n>(): unit diagonal matrix of size m x n
    - support for symbolic computing using Ginac
    - support for meta-expression
    \code
    auto I = integrate(_range=elements(mesh),_expr=_e1 );
    auto v1 = I( idv(v) ).evaluate();
    auto v2 = I( cst(1) ).evaluate();
    \endcode
   - update manual and tutorial, see #61 and #70

## bugs0920 Bugs

   - fixed issue 1: http://code.google.com/p/feelpp/issues/detail?id=1&can=1
   - fixed issue 2: http://code.google.com/p/feelpp/issues/detail?id=2&can=1
   - fixed issue 6: http://code.google.com/p/feelpp/issues/detail?id=6&can=1
   - fixed issue 9: http://code.google.com/p/feelpp/issues/detail?id=9&can=1


# Feel++ Release 0.91.1

   - overall cleanup in C++ preprocessor macros
   - cleanup in cmake
   - fix some compilation issues and added more stringent compiler flags
   - port to boost1.49
   - Fix issues 1, 2 and 9 (see Google Code, http://code.google.com/p/feelpp/issues/list)

# Feel++ Release 0.91.0

## changes0910 Developer changes

   - Feel++ is now seamlessly parallel
   - Feel++ supports seamlessly interpolation in its variational formulation
   language
   - cmake: overall cleanup of cmake feel++ variables which are now prefixed
   FEELPP
    - cmake: in-source builds forbidden
    - cmake: guards againts invalid CMAKE_BUILD_TYPE
    - cmake: added sse, altivec and neon optimizations
    - cmake: fix bug in make_directory
    - cmake: even more minimal configuration in doc/tutorial
    - fix compilation in APPLE and s390 platforms
   - added macport port for feel++ with support for snow leopard and lion
   - Eigen code has been updated to 3.0.5
   - added a config file with extension .cfg based on Boost.program_options in
   Application classes
   - provide systemConfigRepository() and localConfigRepository() in Environment
   class which return respectively the local and system location of the config
   file
   - merge the two implementations of aitken relaxation method and provide a
   simplified interface
   - added interface nlSolve interface to backend similar to solve allowing to
   order-free and optional parameters
   - added interface to external solver libraries via petsc such as mumps or
   umfpack. This is configurable via the config file (.cfg)
   - various fixes in geometric mapping (and inverse) and polynomialset to handle
   objects of topoligical dimension d-1 living in dimension d space.
   - added implementation of $L_2$ and $H_1$ projector which renders rather
   seamless these projection.
   - fix copy/paste bug in bdf extrapolation, the coefficient were divided by dt
   - support for interpolating functions living on meshes of different
   topoligical dimension
   - added mesh elements and faces extraction using createSubmesh() based on mesh
   filters
   - added lift and trace operator, interface might change
   - BDF:
     - new bdf() free function to generate a new bdf `shared_ptr` object and
     configure it
     \code
     // vm is the variable map provided by program options
     // note that by default most option get their value from the command line
     // or config files
     auto mybdf = bdf( _space=Xh, _vm=this->vm(), _order=2, _time_step=0.1 );
     \endcode
   - changed options for bdf: now use . to separate  bdf from rest of option in
     order to be able to create section in config files
   - can pass a prefix to handle several bdf in application
   - GeoTool:
    - update geotool to support markers for 1D meshes
    - added a new Cube object
    - added a pie object
   - added mshconvert() which allows to generate a gmsh mesh out of mesh formats
   supported by gmsh
   - support for passing shared_ptr<> to the differential operators and to on()
   - support in the language for test and trial functions not being defined on the
   same mesh
   - Language:
     - added sym() and antisym() to compute the symmetric and antisymmetric parts of
     a matrix expression
     - added access to expression components via () operator
     - allow integration of test and/or trial functions which are defined  on different
     meshes as well as integrating on a different mesh.
   - reorganized completely and updated/corrected the manual
   - updated doxygen documentation

