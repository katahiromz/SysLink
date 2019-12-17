if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

if (MSVC)
    add_definitions(-DMSVC)
endif()

add_executable(SysLinkDlg WIN32 SysLinkDlg.c SysLinkDlg_res.rc)
target_link_libraries(SysLinkDlg PRIVATE comctl32)
