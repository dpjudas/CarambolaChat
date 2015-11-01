
cmake_minimum_required(VERSION 2.8)
project(carambola-chat)
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -pthread" )
SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=gnu++11 -pthread" )
include_directories(BEFORE CarambolaChat)
add_executable(carambola-chat
    CarambolaChat/precomp.cpp
    CarambolaChat/View/UserList/user_list_view.cpp
    CarambolaChat/View/Chat/chat_line.cpp
    CarambolaChat/View/Chat/chat_view.cpp
    CarambolaChat/View/Theme/theme_views.cpp
    CarambolaChat/View/Workspace/workspace_tab_view.cpp
    CarambolaChat/View/Workspace/workspace_view.cpp
    CarambolaChat/View/Connections/network_list_item_view.cpp
    CarambolaChat/View/Connections/network_list_view.cpp
    CarambolaChat/program.cpp
    CarambolaChat/Model/DCCChat/dcc_chat_connection.cpp
    CarambolaChat/Model/DCCFileTransfer/dcc_file_transfer_connection.cpp
    CarambolaChat/Model/app_model.cpp
    CarambolaChat/Model/IRCSession/irc_message.cpp
    CarambolaChat/Model/IRCSession/command.cpp
    CarambolaChat/Model/IRCSession/irc_text.cpp
    CarambolaChat/Model/IRCSession/irc_connection_queues.cpp
    CarambolaChat/Model/IRCSession/irc_entity.cpp
    CarambolaChat/Model/IRCSession/irc_session.cpp
    CarambolaChat/Model/IRCSession/irc_connection.cpp
    CarambolaChat/Model/XMLSettings/xml_settings_document.cpp
    CarambolaChat/Model/XMLSettings/xml_settings_list.cpp
    CarambolaChat/Model/XMLSettings/xml_settings_map.cpp
    CarambolaChat/Model/XMLSettings/xml_settings.cpp
    CarambolaChat/Model/settings.cpp
    CarambolaChat/Model/IdentServer/ident_server.cpp
    CarambolaChat/Model/IdentServer/ident_server_connection.cpp
    CarambolaChat/Controller/ChatWindow/chat_window_controller.cpp
    CarambolaChat/Controller/Chat/chat_controller.cpp
    CarambolaChat/Controller/About/about_controller.cpp
    CarambolaChat/Controller/EditConnection/edit_connection_controller.cpp
    CarambolaChat/Controller/Workspace/workspace_page_controller.cpp
    CarambolaChat/Controller/Workspace/workspace_controller.cpp
    CarambolaChat/Controller/Workspace/taskbar_notification.cpp
    CarambolaChat/Controller/Connections/connections_controller.cpp
    # CarambolaChat/Model/XMPPSession/xmpp_session.cpp
    # CarambolaChat/Model/XMPPSession/xmpp_stanza.cpp
    # CarambolaChat/Model/XMPPSession/xmpp_connection_queues.cpp
    # CarambolaChat/Model/XMPPSession/xmpp_connection.cpp
)
target_link_libraries(carambola-chat -L/usr/local/include -luicore)
install(TARGETS carambola-chat RUNTIME DESTINATION bin)
install(DIRECTORY CarambolaChat/Resources DESTINATION share)
