##
## Auto Generated makefile, please do not edit
##
WorkspaceName=MUD Development
WorkspacePath=/home/sverre/code/UBSVN/Trunk
ProjectName=Resource

## Debug
ifeq ($(type),Debug)
ConfigurationName=Debug
IntermediateDirectory=./Debug
OutDir=$(IntermediateDirectory)
LinkerName=g++
ArchiveTool=ar rcu
SharedObjectLinkerName=g++ -shared 
ObjectSuffix=.o
DebugSwitch=-g
IncludeSwitch=-I
LibrarySwitch=-l
OutputSwitch=-o
LibraryPathSwitch=-L
PreprocessorSwitch=-D
SourceSwitch=-c
CompilerName=g++
RcCompilerName=
OutputFile=../libmyresource.a
Preprocessors=
CmpOptions=-g -Wall $(Preprocessors)
RcCmpOptions=
LinkOptions=-O0
IncludePath=$(IncludeSwitch). $(IncludeSwitch)../include 
RcIncludePath=
Libs=$(LibrarySwitch)mysqlite 
LibPath=$(LibraryPathSwitch). $(LibraryPathSwitch)./Debug $(LibraryPathSwitch)../ 
endif

Objects=$(IntermediateDirectory)/Base64$(ObjectSuffix) $(IntermediateDirectory)/Database$(ObjectSuffix) $(IntermediateDirectory)/Debug$(ObjectSuffix) $(IntermediateDirectory)/Event$(ObjectSuffix) $(IntermediateDirectory)/EventHandler$(ObjectSuffix) $(IntermediateDirectory)/EventTime$(ObjectSuffix) $(IntermediateDirectory)/File$(ObjectSuffix) $(IntermediateDirectory)/HttpClientSocket$(ObjectSuffix) $(IntermediateDirectory)/HttpdCookies$(ObjectSuffix) $(IntermediateDirectory)/HttpDebugSocket$(ObjectSuffix) \
	$(IntermediateDirectory)/HttpdForm$(ObjectSuffix) $(IntermediateDirectory)/HttpdSocket$(ObjectSuffix) $(IntermediateDirectory)/HttpGetSocket$(ObjectSuffix) $(IntermediateDirectory)/HttpPostSocket$(ObjectSuffix) $(IntermediateDirectory)/HttpPutSocket$(ObjectSuffix) $(IntermediateDirectory)/HTTPSocket$(ObjectSuffix) $(IntermediateDirectory)/IEventOwner$(ObjectSuffix) $(IntermediateDirectory)/Ipv4Address$(ObjectSuffix) $(IntermediateDirectory)/Ipv6Address$(ObjectSuffix) $(IntermediateDirectory)/Lock$(ObjectSuffix) \
	$(IntermediateDirectory)/MemFile$(ObjectSuffix) $(IntermediateDirectory)/Mutex$(ObjectSuffix) $(IntermediateDirectory)/Parse$(ObjectSuffix) $(IntermediateDirectory)/Query$(ObjectSuffix) $(IntermediateDirectory)/RandomNumber$(ObjectSuffix) $(IntermediateDirectory)/ResolvServer$(ObjectSuffix) $(IntermediateDirectory)/ResolvSocket$(ObjectSuffix) $(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix) $(IntermediateDirectory)/Socket$(ObjectSuffix) $(IntermediateDirectory)/SocketHandler$(ObjectSuffix) \
	$(IntermediateDirectory)/socket_include$(ObjectSuffix) $(IntermediateDirectory)/SSLInitializer$(ObjectSuffix) $(IntermediateDirectory)/StderrLog$(ObjectSuffix) $(IntermediateDirectory)/StdoutLog$(ObjectSuffix) $(IntermediateDirectory)/StreamSocket$(ObjectSuffix) $(IntermediateDirectory)/TcpSocket$(ObjectSuffix) $(IntermediateDirectory)/Thread$(ObjectSuffix) $(IntermediateDirectory)/UdpSocket$(ObjectSuffix) $(IntermediateDirectory)/Utility$(ObjectSuffix) $(IntermediateDirectory)/Coordinate$(ObjectSuffix) \
	$(IntermediateDirectory)/Path$(ObjectSuffix) $(IntermediateDirectory)/Global$(ObjectSuffix) $(IntermediateDirectory)/sha2$(ObjectSuffix) $(IntermediateDirectory)/StringUtilities$(ObjectSuffix) $(IntermediateDirectory)/Tables$(ObjectSuffix) $(IntermediateDirectory)/Table$(ObjectSuffix) $(IntermediateDirectory)/Field$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	$(ArchiveTool) $(OutputFile) $(Objects)

./Debug:
	@test -d ./Debug || mkdir ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Base64$(ObjectSuffix): Base64.cpp $(IntermediateDirectory)/Base64$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Base64.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Base64$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Base64$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Base64$(ObjectSuffix) -MF$(IntermediateDirectory)/Base64$(ObjectSuffix).d -MM Base64.cpp

$(IntermediateDirectory)/Database$(ObjectSuffix): Database.cpp $(IntermediateDirectory)/Database$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Database.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Database$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Database$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Database$(ObjectSuffix) -MF$(IntermediateDirectory)/Database$(ObjectSuffix).d -MM Database.cpp

$(IntermediateDirectory)/Debug$(ObjectSuffix): Debug.cpp $(IntermediateDirectory)/Debug$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Debug.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Debug$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Debug$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Debug$(ObjectSuffix) -MF$(IntermediateDirectory)/Debug$(ObjectSuffix).d -MM Debug.cpp

$(IntermediateDirectory)/Event$(ObjectSuffix): Event.cpp $(IntermediateDirectory)/Event$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Event.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Event$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Event$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Event$(ObjectSuffix) -MF$(IntermediateDirectory)/Event$(ObjectSuffix).d -MM Event.cpp

$(IntermediateDirectory)/EventHandler$(ObjectSuffix): EventHandler.cpp $(IntermediateDirectory)/EventHandler$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EventHandler.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EventHandler$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EventHandler$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EventHandler$(ObjectSuffix) -MF$(IntermediateDirectory)/EventHandler$(ObjectSuffix).d -MM EventHandler.cpp

$(IntermediateDirectory)/EventTime$(ObjectSuffix): EventTime.cpp $(IntermediateDirectory)/EventTime$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EventTime.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EventTime$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EventTime$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EventTime$(ObjectSuffix) -MF$(IntermediateDirectory)/EventTime$(ObjectSuffix).d -MM EventTime.cpp

$(IntermediateDirectory)/File$(ObjectSuffix): File.cpp $(IntermediateDirectory)/File$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) File.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/File$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/File$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/File$(ObjectSuffix) -MF$(IntermediateDirectory)/File$(ObjectSuffix).d -MM File.cpp

$(IntermediateDirectory)/HttpClientSocket$(ObjectSuffix): HttpClientSocket.cpp $(IntermediateDirectory)/HttpClientSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) HttpClientSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/HttpClientSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HttpClientSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/HttpClientSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/HttpClientSocket$(ObjectSuffix).d -MM HttpClientSocket.cpp

$(IntermediateDirectory)/HttpdCookies$(ObjectSuffix): HttpdCookies.cpp $(IntermediateDirectory)/HttpdCookies$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) HttpdCookies.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/HttpdCookies$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HttpdCookies$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/HttpdCookies$(ObjectSuffix) -MF$(IntermediateDirectory)/HttpdCookies$(ObjectSuffix).d -MM HttpdCookies.cpp

$(IntermediateDirectory)/HttpDebugSocket$(ObjectSuffix): HttpDebugSocket.cpp $(IntermediateDirectory)/HttpDebugSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) HttpDebugSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/HttpDebugSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HttpDebugSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/HttpDebugSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/HttpDebugSocket$(ObjectSuffix).d -MM HttpDebugSocket.cpp

$(IntermediateDirectory)/HttpdForm$(ObjectSuffix): HttpdForm.cpp $(IntermediateDirectory)/HttpdForm$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) HttpdForm.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/HttpdForm$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HttpdForm$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/HttpdForm$(ObjectSuffix) -MF$(IntermediateDirectory)/HttpdForm$(ObjectSuffix).d -MM HttpdForm.cpp

$(IntermediateDirectory)/HttpdSocket$(ObjectSuffix): HttpdSocket.cpp $(IntermediateDirectory)/HttpdSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) HttpdSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/HttpdSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HttpdSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/HttpdSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/HttpdSocket$(ObjectSuffix).d -MM HttpdSocket.cpp

$(IntermediateDirectory)/HttpGetSocket$(ObjectSuffix): HttpGetSocket.cpp $(IntermediateDirectory)/HttpGetSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) HttpGetSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/HttpGetSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HttpGetSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/HttpGetSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/HttpGetSocket$(ObjectSuffix).d -MM HttpGetSocket.cpp

$(IntermediateDirectory)/HttpPostSocket$(ObjectSuffix): HttpPostSocket.cpp $(IntermediateDirectory)/HttpPostSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) HttpPostSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/HttpPostSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HttpPostSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/HttpPostSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/HttpPostSocket$(ObjectSuffix).d -MM HttpPostSocket.cpp

$(IntermediateDirectory)/HttpPutSocket$(ObjectSuffix): HttpPutSocket.cpp $(IntermediateDirectory)/HttpPutSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) HttpPutSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/HttpPutSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HttpPutSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/HttpPutSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/HttpPutSocket$(ObjectSuffix).d -MM HttpPutSocket.cpp

$(IntermediateDirectory)/HTTPSocket$(ObjectSuffix): HTTPSocket.cpp $(IntermediateDirectory)/HTTPSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) HTTPSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/HTTPSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HTTPSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/HTTPSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/HTTPSocket$(ObjectSuffix).d -MM HTTPSocket.cpp

$(IntermediateDirectory)/IEventOwner$(ObjectSuffix): IEventOwner.cpp $(IntermediateDirectory)/IEventOwner$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) IEventOwner.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/IEventOwner$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IEventOwner$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/IEventOwner$(ObjectSuffix) -MF$(IntermediateDirectory)/IEventOwner$(ObjectSuffix).d -MM IEventOwner.cpp

$(IntermediateDirectory)/Ipv4Address$(ObjectSuffix): Ipv4Address.cpp $(IntermediateDirectory)/Ipv4Address$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Ipv4Address.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Ipv4Address$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Ipv4Address$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Ipv4Address$(ObjectSuffix) -MF$(IntermediateDirectory)/Ipv4Address$(ObjectSuffix).d -MM Ipv4Address.cpp

$(IntermediateDirectory)/Ipv6Address$(ObjectSuffix): Ipv6Address.cpp $(IntermediateDirectory)/Ipv6Address$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Ipv6Address.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Ipv6Address$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Ipv6Address$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Ipv6Address$(ObjectSuffix) -MF$(IntermediateDirectory)/Ipv6Address$(ObjectSuffix).d -MM Ipv6Address.cpp

$(IntermediateDirectory)/Lock$(ObjectSuffix): Lock.cpp $(IntermediateDirectory)/Lock$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Lock.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Lock$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Lock$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Lock$(ObjectSuffix) -MF$(IntermediateDirectory)/Lock$(ObjectSuffix).d -MM Lock.cpp

$(IntermediateDirectory)/MemFile$(ObjectSuffix): MemFile.cpp $(IntermediateDirectory)/MemFile$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) MemFile.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/MemFile$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MemFile$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/MemFile$(ObjectSuffix) -MF$(IntermediateDirectory)/MemFile$(ObjectSuffix).d -MM MemFile.cpp

$(IntermediateDirectory)/Mutex$(ObjectSuffix): Mutex.cpp $(IntermediateDirectory)/Mutex$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Mutex.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Mutex$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Mutex$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Mutex$(ObjectSuffix) -MF$(IntermediateDirectory)/Mutex$(ObjectSuffix).d -MM Mutex.cpp

$(IntermediateDirectory)/Parse$(ObjectSuffix): Parse.cpp $(IntermediateDirectory)/Parse$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Parse.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Parse$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Parse$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Parse$(ObjectSuffix) -MF$(IntermediateDirectory)/Parse$(ObjectSuffix).d -MM Parse.cpp

$(IntermediateDirectory)/Query$(ObjectSuffix): Query.cpp $(IntermediateDirectory)/Query$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Query.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Query$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Query$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Query$(ObjectSuffix) -MF$(IntermediateDirectory)/Query$(ObjectSuffix).d -MM Query.cpp

$(IntermediateDirectory)/RandomNumber$(ObjectSuffix): RandomNumber.cpp $(IntermediateDirectory)/RandomNumber$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) RandomNumber.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/RandomNumber$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/RandomNumber$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/RandomNumber$(ObjectSuffix) -MF$(IntermediateDirectory)/RandomNumber$(ObjectSuffix).d -MM RandomNumber.cpp

$(IntermediateDirectory)/ResolvServer$(ObjectSuffix): ResolvServer.cpp $(IntermediateDirectory)/ResolvServer$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) ResolvServer.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/ResolvServer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ResolvServer$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ResolvServer$(ObjectSuffix) -MF$(IntermediateDirectory)/ResolvServer$(ObjectSuffix).d -MM ResolvServer.cpp

$(IntermediateDirectory)/ResolvSocket$(ObjectSuffix): ResolvSocket.cpp $(IntermediateDirectory)/ResolvSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) ResolvSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/ResolvSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ResolvSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ResolvSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/ResolvSocket$(ObjectSuffix).d -MM ResolvSocket.cpp

$(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix): SmtpdSocket.cpp $(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) SmtpdSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix).d -MM SmtpdSocket.cpp

$(IntermediateDirectory)/Socket$(ObjectSuffix): Socket.cpp $(IntermediateDirectory)/Socket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Socket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Socket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Socket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Socket$(ObjectSuffix) -MF$(IntermediateDirectory)/Socket$(ObjectSuffix).d -MM Socket.cpp

$(IntermediateDirectory)/SocketHandler$(ObjectSuffix): SocketHandler.cpp $(IntermediateDirectory)/SocketHandler$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) SocketHandler.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/SocketHandler$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SocketHandler$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SocketHandler$(ObjectSuffix) -MF$(IntermediateDirectory)/SocketHandler$(ObjectSuffix).d -MM SocketHandler.cpp

$(IntermediateDirectory)/socket_include$(ObjectSuffix): socket_include.cpp $(IntermediateDirectory)/socket_include$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) socket_include.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/socket_include$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/socket_include$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/socket_include$(ObjectSuffix) -MF$(IntermediateDirectory)/socket_include$(ObjectSuffix).d -MM socket_include.cpp

$(IntermediateDirectory)/SSLInitializer$(ObjectSuffix): SSLInitializer.cpp $(IntermediateDirectory)/SSLInitializer$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) SSLInitializer.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/SSLInitializer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SSLInitializer$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SSLInitializer$(ObjectSuffix) -MF$(IntermediateDirectory)/SSLInitializer$(ObjectSuffix).d -MM SSLInitializer.cpp

$(IntermediateDirectory)/StderrLog$(ObjectSuffix): StderrLog.cpp $(IntermediateDirectory)/StderrLog$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) StderrLog.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/StderrLog$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StderrLog$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/StderrLog$(ObjectSuffix) -MF$(IntermediateDirectory)/StderrLog$(ObjectSuffix).d -MM StderrLog.cpp

$(IntermediateDirectory)/StdoutLog$(ObjectSuffix): StdoutLog.cpp $(IntermediateDirectory)/StdoutLog$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) StdoutLog.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/StdoutLog$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StdoutLog$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/StdoutLog$(ObjectSuffix) -MF$(IntermediateDirectory)/StdoutLog$(ObjectSuffix).d -MM StdoutLog.cpp

$(IntermediateDirectory)/StreamSocket$(ObjectSuffix): StreamSocket.cpp $(IntermediateDirectory)/StreamSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) StreamSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/StreamSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StreamSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/StreamSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/StreamSocket$(ObjectSuffix).d -MM StreamSocket.cpp

$(IntermediateDirectory)/TcpSocket$(ObjectSuffix): TcpSocket.cpp $(IntermediateDirectory)/TcpSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) TcpSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/TcpSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TcpSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/TcpSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/TcpSocket$(ObjectSuffix).d -MM TcpSocket.cpp

$(IntermediateDirectory)/Thread$(ObjectSuffix): Thread.cpp $(IntermediateDirectory)/Thread$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Thread.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Thread$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Thread$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Thread$(ObjectSuffix) -MF$(IntermediateDirectory)/Thread$(ObjectSuffix).d -MM Thread.cpp

$(IntermediateDirectory)/UdpSocket$(ObjectSuffix): UdpSocket.cpp $(IntermediateDirectory)/UdpSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) UdpSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/UdpSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UdpSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/UdpSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/UdpSocket$(ObjectSuffix).d -MM UdpSocket.cpp

$(IntermediateDirectory)/Utility$(ObjectSuffix): Utility.cpp $(IntermediateDirectory)/Utility$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Utility.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Utility$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Utility$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Utility$(ObjectSuffix) -MF$(IntermediateDirectory)/Utility$(ObjectSuffix).d -MM Utility.cpp

$(IntermediateDirectory)/Coordinate$(ObjectSuffix): Coordinate.cpp $(IntermediateDirectory)/Coordinate$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Coordinate.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Coordinate$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Coordinate$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Coordinate$(ObjectSuffix) -MF$(IntermediateDirectory)/Coordinate$(ObjectSuffix).d -MM Coordinate.cpp

$(IntermediateDirectory)/Path$(ObjectSuffix): Path.cpp $(IntermediateDirectory)/Path$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Path.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Path$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Path$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Path$(ObjectSuffix) -MF$(IntermediateDirectory)/Path$(ObjectSuffix).d -MM Path.cpp

$(IntermediateDirectory)/Global$(ObjectSuffix): Global.cpp $(IntermediateDirectory)/Global$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Global.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Global$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Global$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Global$(ObjectSuffix) -MF$(IntermediateDirectory)/Global$(ObjectSuffix).d -MM Global.cpp

$(IntermediateDirectory)/sha2$(ObjectSuffix): sha2.c $(IntermediateDirectory)/sha2$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) sha2.c $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/sha2$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sha2$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/sha2$(ObjectSuffix) -MF$(IntermediateDirectory)/sha2$(ObjectSuffix).d -MM sha2.c

$(IntermediateDirectory)/StringUtilities$(ObjectSuffix): StringUtilities.cpp $(IntermediateDirectory)/StringUtilities$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) StringUtilities.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/StringUtilities$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StringUtilities$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/StringUtilities$(ObjectSuffix) -MF$(IntermediateDirectory)/StringUtilities$(ObjectSuffix).d -MM StringUtilities.cpp

$(IntermediateDirectory)/Tables$(ObjectSuffix): Tables.cpp $(IntermediateDirectory)/Tables$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Tables.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Tables$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Tables$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Tables$(ObjectSuffix) -MF$(IntermediateDirectory)/Tables$(ObjectSuffix).d -MM Tables.cpp

$(IntermediateDirectory)/Table$(ObjectSuffix): Table.cpp $(IntermediateDirectory)/Table$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Table.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Table$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Table$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Table$(ObjectSuffix) -MF$(IntermediateDirectory)/Table$(ObjectSuffix).d -MM Table.cpp

$(IntermediateDirectory)/Field$(ObjectSuffix): Field.cpp $(IntermediateDirectory)/Field$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Field.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Field$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Field$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Field$(ObjectSuffix) -MF$(IntermediateDirectory)/Field$(ObjectSuffix).d -MM Field.cpp

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Base64$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Base64$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Database$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Database$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Debug$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Debug$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Event$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Event$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EventHandler$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EventHandler$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EventTime$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EventTime$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/File$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/File$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/HttpClientSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/HttpClientSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/HttpdCookies$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/HttpdCookies$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/HttpDebugSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/HttpDebugSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/HttpdForm$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/HttpdForm$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/HttpdSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/HttpdSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/HttpGetSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/HttpGetSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/HttpPostSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/HttpPostSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/HttpPutSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/HttpPutSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/HTTPSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/HTTPSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/IEventOwner$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/IEventOwner$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Ipv4Address$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Ipv4Address$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Ipv6Address$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Ipv6Address$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Lock$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Lock$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/MemFile$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/MemFile$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Mutex$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Mutex$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Parse$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Parse$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Query$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Query$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/RandomNumber$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/RandomNumber$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/ResolvServer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ResolvServer$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/ResolvSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ResolvSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Socket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Socket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/SocketHandler$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SocketHandler$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/socket_include$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/socket_include$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/SSLInitializer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SSLInitializer$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/StderrLog$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/StderrLog$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/StdoutLog$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/StdoutLog$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/StreamSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/StreamSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/TcpSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/TcpSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Thread$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Thread$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/UdpSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/UdpSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Utility$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Utility$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Coordinate$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Coordinate$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Path$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Path$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Global$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Global$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/sha2$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sha2$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/StringUtilities$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/StringUtilities$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Tables$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Tables$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Table$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Table$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Field$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Field$(ObjectSuffix).d
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*.d

