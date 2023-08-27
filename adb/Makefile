SRCS+= adb.c
SRCS+= adb_auth_host.c
SRCS+= adb_client.c
SRCS+= commandline.c
SRCS+= console.c
SRCS+= fdevent.c
SRCS+= file_sync_client.c
SRCS+= get_my_path_linux.c
SRCS+= services.c
SRCS+= sockets.c
SRCS+= transport.c
SRCS+= transport_local.c
SRCS+= transport_usb.c
SRCS+= usb_linux.c

VPATH+= ../libcutils
SRCS+= load_file.c
SRCS+= socket_inaddr_any_server.c
SRCS+= socket_local_client.c
SRCS+= socket_local_server.c
SRCS+= socket_loopback_client.c
SRCS+= socket_loopback_server.c
SRCS+= socket_network_client.c

ADB_CPPFLAGS+= -DADB_HOST=1
CPPFLAGS+= -DHAVE_FORKEXEC=1
CPPFLAGS+= -I.
CPPFLAGS+= -I../include
CPPFLAGS+= -D_FILE_OFFSET_BITS=64
CPPFLAGS+= -D_XOPEN_SOURCE
CPPFLAGS+= -D_GNU_SOURCE

ADB_LIBS+= -lcrypto -lpthread

OBJS= $(SRCS:.c=.adb.o)
%.adb.o: %.c
	$(CC) -c $(ADB_CPPFLAGS) $(CPPFLAGS) -o $@ $<

ADBD_CPPFLAGS+= -DADB_HOST=0
ADBD_CPPFLAGS+= -DALLOW_ADBD_ROOT=1

ADBD_SRCS+= adb.c
ADBD_SRCS+= fdevent.c
ADBD_SRCS+= transport.c
ADBD_SRCS+= transport_local.c
ADBD_SRCS+= transport_usb.c
ADBD_SRCS+= sockets.c
ADBD_SRCS+= services.c
ADBD_SRCS+= file_sync_service.c
ADBD_SRCS+= jdwp_service.c
ADBD_SRCS+= usb_linux_client.c
ADBD_SRCS+= udc_controller.c

ADBD_SRCS+= socket_inaddr_any_server.c
ADBD_SRCS+= socket_local_client.c
ADBD_SRCS+= socket_local_server.c
ADBD_SRCS+= socket_loopback_client.c
ADBD_SRCS+= socket_loopback_server.c

ADBD_LIBS+= -lpthread

ADBD_OBJS= $(ADBD_SRCS:.c=.adbd.o)
%.adbd.o: %.c
	$(CC) -c $(ADBD_CPPFLAGS) $(CPPFLAGS) -o $@ $<

all: adb adbd

adb: $(OBJS)
	$(CC) -o $@ $(ADB_CPPFLAGS) $(LDFLAGS) $(OBJS) $(ADB_LIBS)

adbd: $(ADBD_OBJS)
	$(CC) -o $@ $(ADBD_CPPFLAGS) $(LDFLAGS) $(ADBD_OBJS) $(ADBD_LIBS)
