EXAMPLE_BIN=CarambolaChat/carambola
OBJF =  CarambolaChat/precomp.o \
 CarambolaChat/View/UserList/user_list_view.o \
 CarambolaChat/View/Chat/chat_line.o \
 CarambolaChat/View/Chat/chat_view.o \
 CarambolaChat/View/Theme/theme_views.o \
 CarambolaChat/View/Workspace/workspace_tab_view.o \
 CarambolaChat/View/Workspace/workspace_view.o \
 CarambolaChat/View/Connections/network_list_item_view.o \
 CarambolaChat/View/Connections/network_list_view.o \
 CarambolaChat/program.o \
 CarambolaChat/Model/DCCChat/dcc_chat_connection.o \
 CarambolaChat/Model/DCCFileTransfer/dcc_file_transfer_connection.o \
 CarambolaChat/Model/app_model.o \
 CarambolaChat/Model/IRCSession/irc_message.o \
 CarambolaChat/Model/IRCSession/command.o \
 CarambolaChat/Model/IRCSession/irc_text.o \
 CarambolaChat/Model/IRCSession/irc_connection_queues.o \
 CarambolaChat/Model/IRCSession/irc_entity.o \
 CarambolaChat/Model/IRCSession/irc_session.o \
 CarambolaChat/Model/IRCSession/irc_connection.o \
 CarambolaChat/Model/XMLSettings/xml_settings_document.o \
 CarambolaChat/Model/XMLSettings/xml_settings_list.o \
 CarambolaChat/Model/XMLSettings/xml_settings_map.o \
 CarambolaChat/Model/XMLSettings/xml_settings.o \
 CarambolaChat/Model/settings.o \
 CarambolaChat/Model/XMPPSession/xmpp_session.o \
 CarambolaChat/Model/XMPPSession/xmpp_stanza.o \
 CarambolaChat/Model/XMPPSession/xmpp_connection_queues.o \
 CarambolaChat/Model/XMPPSession/xmpp_connection.o \
 CarambolaChat/Model/IdentServer/ident_server.o \
 CarambolaChat/Model/IdentServer/ident_server_connection.o \
 CarambolaChat/Controller/ChatWindow/chat_window_controller.o \
 CarambolaChat/Controller/Chat/chat_controller.o \
 CarambolaChat/Controller/About/about_controller.o \
 CarambolaChat/Controller/EditConnection/edit_connection_controller.o \
 CarambolaChat/Controller/Workspace/workspace_page_controller.o \
 CarambolaChat/Controller/Workspace/workspace_controller.o \
 CarambolaChat/Controller/Workspace/taskbar_notification.o \
 CarambolaChat/Controller/Connections/connections_controller.o

LIBS=clanApp clanDisplay clanCore clanGL clanUI clanSound clanNetwork

CXXFLAGS += -I./ -I CarambolaChat

PACKAGES = $(patsubst %,%-4.0,$(LIBS))
CXXFLAGS += `pkg-config --cflags $(PACKAGES)` -pthread
LDFLAGS += -ldl

all: $(EXAMPLE_BIN)

$(EXAMPLE_BIN): $(OBJF)
	$(CXX) $(CXXFLAGS) $(OBJF) -o $(EXAMPLE_BIN) `pkg-config --libs $(PACKAGES)` $(EXTRA_LIBS)

clean:
	rm -f $(OBJF) $(EXAMPLE_BIN)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# EOF #

