set_directory_properties(PROPERTIES LABEL testvf )

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR} )

feelpp_add_test( ginac )
feelpp_add_test( inner CFG test_inner.cfg )
feelpp_add_test( laplacianv CFG test_laplacianv.cfg )
feelpp_add_test( laplacian CFG test_laplacian.cfg )
feelpp_add_test( laplaciant CFG test_laplaciant.cfg )
feelpp_add_test( msi CFG test_msi.cfg )
feelpp_add_test( inner_curl )
feelpp_add_test( inner_laplacian )

feelpp_add_test( projtangent )
