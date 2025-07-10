include("/home/mana/chat_Client/build/Desktop_Qt_6_9_1-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/chat_Client-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/mana/chat_Client/build/Desktop_Qt_6_9_1-Debug/chat_Client
    GENERATE_QT_CONF
)
