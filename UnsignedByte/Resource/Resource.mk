##
## Auto Generated makefile, please do not edit
##
ProjectName=Resource

## Debug
ifeq ($(type),Debug)
ConfigurationName=Debug
IntermediateDirectory=./Debug
OutDir=$(IntermediateDirectory)
LinkerName=g++
ArchiveTool=ar rcu
SharedObjectLinkerName=g++ -shared -fPIC
ObjectSuffix=.o
DebugSwitch=-gstab
IncludeSwitch=-I
LibrarySwitch=-l
OutputSwitch=-o 
LibraryPathSwitch=-L
PreprocessorSwitch=-D
SourceSwitch=-c 
CompilerName=g++
RcCompilerName=windres
OutputFile=../lib/libubresource.a
Preprocessors=
ObjectSwitch=-o 
ArchiveOutputSwitch= 
CmpOptions=-g -Wall $(Preprocessors)
RcCmpOptions=
LinkOptions=-O0
IncludePath=$(IncludeSwitch). $(IncludeSwitch)../include $(IncludeSwitch)$(HOME)/local/include 
RcIncludePath=
Libs=
LibPath=$(LibraryPathSwitch). 
endif

Objects=$(IntermediateDirectory)/Coordinate$(ObjectSuffix) $(IntermediateDirectory)/Path$(ObjectSuffix) $(IntermediateDirectory)/Global$(ObjectSuffix) $(IntermediateDirectory)/sha2$(ObjectSuffix) $(IntermediateDirectory)/StringUtilities$(ObjectSuffix) $(IntermediateDirectory)/Tables$(ObjectSuffix) $(IntermediateDirectory)/Table$(ObjectSuffix) $(IntermediateDirectory)/Field$(ObjectSuffix) $(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix) $(IntermediateDirectory)/SqliteMgr$(ObjectSuffix) \
	$(IntermediateDirectory)/Statements$(ObjectSuffix) $(IntermediateDirectory)/ListActor$(ObjectSuffix) $(IntermediateDirectory)/CountActor$(ObjectSuffix) $(IntermediateDirectory)/SPKCriteria$(ObjectSuffix) $(IntermediateDirectory)/SavableManager$(ObjectSuffix) $(IntermediateDirectory)/FieldDef$(ObjectSuffix) $(IntermediateDirectory)/FieldImpl$(ObjectSuffix) $(IntermediateDirectory)/TableDef$(ObjectSuffix) $(IntermediateDirectory)/TableImpl$(ObjectSuffix) $(IntermediateDirectory)/Keys$(ObjectSuffix) \
	$(IntermediateDirectory)/MPKCriteria$(ObjectSuffix) $(IntermediateDirectory)/SqliteError$(ObjectSuffix) $(IntermediateDirectory)/Assert$(ObjectSuffix) $(IntermediateDirectory)/Value$(ObjectSuffix) $(IntermediateDirectory)/Criteria$(ObjectSuffix) $(IntermediateDirectory)/Key$(ObjectSuffix) $(IntermediateDirectory)/Base64$(ObjectSuffix) $(IntermediateDirectory)/Event$(ObjectSuffix) $(IntermediateDirectory)/EventHandler$(ObjectSuffix) $(IntermediateDirectory)/Database$(ObjectSuffix) \
	$(IntermediateDirectory)/Debug$(ObjectSuffix) $(IntermediateDirectory)/EventTime$(ObjectSuffix) $(IntermediateDirectory)/File$(ObjectSuffix) $(IntermediateDirectory)/IEventOwner$(ObjectSuffix) $(IntermediateDirectory)/Ipv4Address$(ObjectSuffix) $(IntermediateDirectory)/Ipv6Address$(ObjectSuffix) $(IntermediateDirectory)/Mutex$(ObjectSuffix) $(IntermediateDirectory)/MemFile$(ObjectSuffix) $(IntermediateDirectory)/Lock$(ObjectSuffix) $(IntermediateDirectory)/Parse$(ObjectSuffix) \
	$(IntermediateDirectory)/ResolvServer$(ObjectSuffix) $(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix) $(IntermediateDirectory)/ResolvSocket$(ObjectSuffix) $(IntermediateDirectory)/Query$(ObjectSuffix) $(IntermediateDirectory)/RandomNumber$(ObjectSuffix) $(IntermediateDirectory)/SSLInitializer$(ObjectSuffix) $(IntermediateDirectory)/SocketHandler$(ObjectSuffix) $(IntermediateDirectory)/StderrLog$(ObjectSuffix) $(IntermediateDirectory)/socket_include$(ObjectSuffix) $(IntermediateDirectory)/StreamSocket$(ObjectSuffix) \
	$(IntermediateDirectory)/StdoutLog$(ObjectSuffix) $(IntermediateDirectory)/Socket$(ObjectSuffix) $(IntermediateDirectory)/TcpSocket$(ObjectSuffix) $(IntermediateDirectory)/Thread$(ObjectSuffix) $(IntermediateDirectory)/Utility$(ObjectSuffix) $(IntermediateDirectory)/UdpSocket$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): PrePreBuild $(Objects)
	$(ArchiveTool) $(ArchiveOutputSwitch)$(OutputFile) $(Objects)

./Debug:
	@test -d ./Debug || mkdir ./Debug

PrePreBuild: 



PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Coordinate$(ObjectSuffix): Coordinate.cpp $(IntermediateDirectory)/Coordinate$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Coordinate.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Coordinate$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Coordinate$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Coordinate$(ObjectSuffix) -MF$(IntermediateDirectory)/Coordinate$(ObjectSuffix).d -MM Coordinate.cpp

$(IntermediateDirectory)/Path$(ObjectSuffix): Path.cpp $(IntermediateDirectory)/Path$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Path.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Path$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Path$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Path$(ObjectSuffix) -MF$(IntermediateDirectory)/Path$(ObjectSuffix).d -MM Path.cpp

$(IntermediateDirectory)/Global$(ObjectSuffix): Global.cpp $(IntermediateDirectory)/Global$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Global.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Global$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Global$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Global$(ObjectSuffix) -MF$(IntermediateDirectory)/Global$(ObjectSuffix).d -MM Global.cpp

$(IntermediateDirectory)/sha2$(ObjectSuffix): sha2.c $(IntermediateDirectory)/sha2$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)sha2.c $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/sha2$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sha2$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/sha2$(ObjectSuffix) -MF$(IntermediateDirectory)/sha2$(ObjectSuffix).d -MM sha2.c

$(IntermediateDirectory)/StringUtilities$(ObjectSuffix): StringUtilities.cpp $(IntermediateDirectory)/StringUtilities$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)StringUtilities.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/StringUtilities$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StringUtilities$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/StringUtilities$(ObjectSuffix) -MF$(IntermediateDirectory)/StringUtilities$(ObjectSuffix).d -MM StringUtilities.cpp

$(IntermediateDirectory)/Tables$(ObjectSuffix): Tables.cpp $(IntermediateDirectory)/Tables$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Tables.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Tables$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Tables$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Tables$(ObjectSuffix) -MF$(IntermediateDirectory)/Tables$(ObjectSuffix).d -MM Tables.cpp

$(IntermediateDirectory)/Table$(ObjectSuffix): Table.cpp $(IntermediateDirectory)/Table$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Table.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Table$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Table$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Table$(ObjectSuffix) -MF$(IntermediateDirectory)/Table$(ObjectSuffix).d -MM Table.cpp

$(IntermediateDirectory)/Field$(ObjectSuffix): Field.cpp $(IntermediateDirectory)/Field$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Field.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Field$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Field$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Field$(ObjectSuffix) -MF$(IntermediateDirectory)/Field$(ObjectSuffix).d -MM Field.cpp

$(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix): DatabaseMgr.cpp $(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)DatabaseMgr.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix) -MF$(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix).d -MM DatabaseMgr.cpp

$(IntermediateDirectory)/SqliteMgr$(ObjectSuffix): SqliteMgr.cpp $(IntermediateDirectory)/SqliteMgr$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)SqliteMgr.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/SqliteMgr$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SqliteMgr$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SqliteMgr$(ObjectSuffix) -MF$(IntermediateDirectory)/SqliteMgr$(ObjectSuffix).d -MM SqliteMgr.cpp

$(IntermediateDirectory)/Statements$(ObjectSuffix): Statements.cpp $(IntermediateDirectory)/Statements$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Statements.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Statements$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Statements$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Statements$(ObjectSuffix) -MF$(IntermediateDirectory)/Statements$(ObjectSuffix).d -MM Statements.cpp

$(IntermediateDirectory)/ListActor$(ObjectSuffix): ListActor.cpp $(IntermediateDirectory)/ListActor$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)ListActor.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/ListActor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ListActor$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ListActor$(ObjectSuffix) -MF$(IntermediateDirectory)/ListActor$(ObjectSuffix).d -MM ListActor.cpp

$(IntermediateDirectory)/CountActor$(ObjectSuffix): CountActor.cpp $(IntermediateDirectory)/CountActor$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)CountActor.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/CountActor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CountActor$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/CountActor$(ObjectSuffix) -MF$(IntermediateDirectory)/CountActor$(ObjectSuffix).d -MM CountActor.cpp

$(IntermediateDirectory)/SPKCriteria$(ObjectSuffix): SPKCriteria.cpp $(IntermediateDirectory)/SPKCriteria$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)SPKCriteria.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/SPKCriteria$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SPKCriteria$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SPKCriteria$(ObjectSuffix) -MF$(IntermediateDirectory)/SPKCriteria$(ObjectSuffix).d -MM SPKCriteria.cpp

$(IntermediateDirectory)/SavableManager$(ObjectSuffix): SavableManager.cpp $(IntermediateDirectory)/SavableManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)SavableManager.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/SavableManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SavableManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SavableManager$(ObjectSuffix) -MF$(IntermediateDirectory)/SavableManager$(ObjectSuffix).d -MM SavableManager.cpp

$(IntermediateDirectory)/FieldDef$(ObjectSuffix): FieldDef.cpp $(IntermediateDirectory)/FieldDef$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)FieldDef.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/FieldDef$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FieldDef$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/FieldDef$(ObjectSuffix) -MF$(IntermediateDirectory)/FieldDef$(ObjectSuffix).d -MM FieldDef.cpp

$(IntermediateDirectory)/FieldImpl$(ObjectSuffix): FieldImpl.cpp $(IntermediateDirectory)/FieldImpl$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)FieldImpl.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/FieldImpl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FieldImpl$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/FieldImpl$(ObjectSuffix) -MF$(IntermediateDirectory)/FieldImpl$(ObjectSuffix).d -MM FieldImpl.cpp

$(IntermediateDirectory)/TableDef$(ObjectSuffix): TableDef.cpp $(IntermediateDirectory)/TableDef$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)TableDef.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/TableDef$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TableDef$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/TableDef$(ObjectSuffix) -MF$(IntermediateDirectory)/TableDef$(ObjectSuffix).d -MM TableDef.cpp

$(IntermediateDirectory)/TableImpl$(ObjectSuffix): TableImpl.cpp $(IntermediateDirectory)/TableImpl$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)TableImpl.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/TableImpl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TableImpl$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/TableImpl$(ObjectSuffix) -MF$(IntermediateDirectory)/TableImpl$(ObjectSuffix).d -MM TableImpl.cpp

$(IntermediateDirectory)/Keys$(ObjectSuffix): Keys.cpp $(IntermediateDirectory)/Keys$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Keys.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Keys$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Keys$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Keys$(ObjectSuffix) -MF$(IntermediateDirectory)/Keys$(ObjectSuffix).d -MM Keys.cpp

$(IntermediateDirectory)/MPKCriteria$(ObjectSuffix): MPKCriteria.cpp $(IntermediateDirectory)/MPKCriteria$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)MPKCriteria.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/MPKCriteria$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MPKCriteria$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/MPKCriteria$(ObjectSuffix) -MF$(IntermediateDirectory)/MPKCriteria$(ObjectSuffix).d -MM MPKCriteria.cpp

$(IntermediateDirectory)/SqliteError$(ObjectSuffix): SqliteError.cpp $(IntermediateDirectory)/SqliteError$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)SqliteError.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/SqliteError$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SqliteError$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SqliteError$(ObjectSuffix) -MF$(IntermediateDirectory)/SqliteError$(ObjectSuffix).d -MM SqliteError.cpp

$(IntermediateDirectory)/Assert$(ObjectSuffix): Assert.cpp $(IntermediateDirectory)/Assert$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Assert.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Assert$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Assert$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Assert$(ObjectSuffix) -MF$(IntermediateDirectory)/Assert$(ObjectSuffix).d -MM Assert.cpp

$(IntermediateDirectory)/Value$(ObjectSuffix): Value.cpp $(IntermediateDirectory)/Value$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Value.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Value$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Value$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Value$(ObjectSuffix) -MF$(IntermediateDirectory)/Value$(ObjectSuffix).d -MM Value.cpp

$(IntermediateDirectory)/Criteria$(ObjectSuffix): Criteria.cpp $(IntermediateDirectory)/Criteria$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Criteria.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Criteria$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Criteria$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Criteria$(ObjectSuffix) -MF$(IntermediateDirectory)/Criteria$(ObjectSuffix).d -MM Criteria.cpp

$(IntermediateDirectory)/Key$(ObjectSuffix): Key.cpp $(IntermediateDirectory)/Key$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Key.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Key$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Key$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Key$(ObjectSuffix) -MF$(IntermediateDirectory)/Key$(ObjectSuffix).d -MM Key.cpp

$(IntermediateDirectory)/Base64$(ObjectSuffix): Base64.cpp $(IntermediateDirectory)/Base64$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Base64.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Base64$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Base64$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Base64$(ObjectSuffix) -MF$(IntermediateDirectory)/Base64$(ObjectSuffix).d -MM Base64.cpp

$(IntermediateDirectory)/Event$(ObjectSuffix): Event.cpp $(IntermediateDirectory)/Event$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Event.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Event$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Event$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Event$(ObjectSuffix) -MF$(IntermediateDirectory)/Event$(ObjectSuffix).d -MM Event.cpp

$(IntermediateDirectory)/EventHandler$(ObjectSuffix): EventHandler.cpp $(IntermediateDirectory)/EventHandler$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EventHandler.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/EventHandler$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EventHandler$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EventHandler$(ObjectSuffix) -MF$(IntermediateDirectory)/EventHandler$(ObjectSuffix).d -MM EventHandler.cpp

$(IntermediateDirectory)/Database$(ObjectSuffix): Database.cpp $(IntermediateDirectory)/Database$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Database.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Database$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Database$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Database$(ObjectSuffix) -MF$(IntermediateDirectory)/Database$(ObjectSuffix).d -MM Database.cpp

$(IntermediateDirectory)/Debug$(ObjectSuffix): Debug.cpp $(IntermediateDirectory)/Debug$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Debug.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Debug$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Debug$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Debug$(ObjectSuffix) -MF$(IntermediateDirectory)/Debug$(ObjectSuffix).d -MM Debug.cpp

$(IntermediateDirectory)/EventTime$(ObjectSuffix): EventTime.cpp $(IntermediateDirectory)/EventTime$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EventTime.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/EventTime$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EventTime$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EventTime$(ObjectSuffix) -MF$(IntermediateDirectory)/EventTime$(ObjectSuffix).d -MM EventTime.cpp

$(IntermediateDirectory)/File$(ObjectSuffix): File.cpp $(IntermediateDirectory)/File$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)File.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/File$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/File$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/File$(ObjectSuffix) -MF$(IntermediateDirectory)/File$(ObjectSuffix).d -MM File.cpp

$(IntermediateDirectory)/IEventOwner$(ObjectSuffix): IEventOwner.cpp $(IntermediateDirectory)/IEventOwner$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)IEventOwner.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/IEventOwner$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IEventOwner$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/IEventOwner$(ObjectSuffix) -MF$(IntermediateDirectory)/IEventOwner$(ObjectSuffix).d -MM IEventOwner.cpp

$(IntermediateDirectory)/Ipv4Address$(ObjectSuffix): Ipv4Address.cpp $(IntermediateDirectory)/Ipv4Address$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Ipv4Address.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Ipv4Address$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Ipv4Address$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Ipv4Address$(ObjectSuffix) -MF$(IntermediateDirectory)/Ipv4Address$(ObjectSuffix).d -MM Ipv4Address.cpp

$(IntermediateDirectory)/Ipv6Address$(ObjectSuffix): Ipv6Address.cpp $(IntermediateDirectory)/Ipv6Address$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Ipv6Address.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Ipv6Address$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Ipv6Address$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Ipv6Address$(ObjectSuffix) -MF$(IntermediateDirectory)/Ipv6Address$(ObjectSuffix).d -MM Ipv6Address.cpp

$(IntermediateDirectory)/Mutex$(ObjectSuffix): Mutex.cpp $(IntermediateDirectory)/Mutex$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Mutex.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Mutex$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Mutex$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Mutex$(ObjectSuffix) -MF$(IntermediateDirectory)/Mutex$(ObjectSuffix).d -MM Mutex.cpp

$(IntermediateDirectory)/MemFile$(ObjectSuffix): MemFile.cpp $(IntermediateDirectory)/MemFile$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)MemFile.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/MemFile$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MemFile$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/MemFile$(ObjectSuffix) -MF$(IntermediateDirectory)/MemFile$(ObjectSuffix).d -MM MemFile.cpp

$(IntermediateDirectory)/Lock$(ObjectSuffix): Lock.cpp $(IntermediateDirectory)/Lock$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Lock.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Lock$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Lock$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Lock$(ObjectSuffix) -MF$(IntermediateDirectory)/Lock$(ObjectSuffix).d -MM Lock.cpp

$(IntermediateDirectory)/Parse$(ObjectSuffix): Parse.cpp $(IntermediateDirectory)/Parse$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Parse.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Parse$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Parse$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Parse$(ObjectSuffix) -MF$(IntermediateDirectory)/Parse$(ObjectSuffix).d -MM Parse.cpp

$(IntermediateDirectory)/ResolvServer$(ObjectSuffix): ResolvServer.cpp $(IntermediateDirectory)/ResolvServer$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)ResolvServer.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/ResolvServer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ResolvServer$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ResolvServer$(ObjectSuffix) -MF$(IntermediateDirectory)/ResolvServer$(ObjectSuffix).d -MM ResolvServer.cpp

$(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix): SmtpdSocket.cpp $(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)SmtpdSocket.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix).d -MM SmtpdSocket.cpp

$(IntermediateDirectory)/ResolvSocket$(ObjectSuffix): ResolvSocket.cpp $(IntermediateDirectory)/ResolvSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)ResolvSocket.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/ResolvSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ResolvSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ResolvSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/ResolvSocket$(ObjectSuffix).d -MM ResolvSocket.cpp

$(IntermediateDirectory)/Query$(ObjectSuffix): Query.cpp $(IntermediateDirectory)/Query$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Query.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Query$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Query$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Query$(ObjectSuffix) -MF$(IntermediateDirectory)/Query$(ObjectSuffix).d -MM Query.cpp

$(IntermediateDirectory)/RandomNumber$(ObjectSuffix): RandomNumber.cpp $(IntermediateDirectory)/RandomNumber$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)RandomNumber.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/RandomNumber$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/RandomNumber$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/RandomNumber$(ObjectSuffix) -MF$(IntermediateDirectory)/RandomNumber$(ObjectSuffix).d -MM RandomNumber.cpp

$(IntermediateDirectory)/SSLInitializer$(ObjectSuffix): SSLInitializer.cpp $(IntermediateDirectory)/SSLInitializer$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)SSLInitializer.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/SSLInitializer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SSLInitializer$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SSLInitializer$(ObjectSuffix) -MF$(IntermediateDirectory)/SSLInitializer$(ObjectSuffix).d -MM SSLInitializer.cpp

$(IntermediateDirectory)/SocketHandler$(ObjectSuffix): SocketHandler.cpp $(IntermediateDirectory)/SocketHandler$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)SocketHandler.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/SocketHandler$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SocketHandler$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SocketHandler$(ObjectSuffix) -MF$(IntermediateDirectory)/SocketHandler$(ObjectSuffix).d -MM SocketHandler.cpp

$(IntermediateDirectory)/StderrLog$(ObjectSuffix): StderrLog.cpp $(IntermediateDirectory)/StderrLog$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)StderrLog.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/StderrLog$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StderrLog$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/StderrLog$(ObjectSuffix) -MF$(IntermediateDirectory)/StderrLog$(ObjectSuffix).d -MM StderrLog.cpp

$(IntermediateDirectory)/socket_include$(ObjectSuffix): socket_include.cpp $(IntermediateDirectory)/socket_include$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)socket_include.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/socket_include$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/socket_include$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/socket_include$(ObjectSuffix) -MF$(IntermediateDirectory)/socket_include$(ObjectSuffix).d -MM socket_include.cpp

$(IntermediateDirectory)/StreamSocket$(ObjectSuffix): StreamSocket.cpp $(IntermediateDirectory)/StreamSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)StreamSocket.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/StreamSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StreamSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/StreamSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/StreamSocket$(ObjectSuffix).d -MM StreamSocket.cpp

$(IntermediateDirectory)/StdoutLog$(ObjectSuffix): StdoutLog.cpp $(IntermediateDirectory)/StdoutLog$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)StdoutLog.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/StdoutLog$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StdoutLog$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/StdoutLog$(ObjectSuffix) -MF$(IntermediateDirectory)/StdoutLog$(ObjectSuffix).d -MM StdoutLog.cpp

$(IntermediateDirectory)/Socket$(ObjectSuffix): Socket.cpp $(IntermediateDirectory)/Socket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Socket.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Socket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Socket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Socket$(ObjectSuffix) -MF$(IntermediateDirectory)/Socket$(ObjectSuffix).d -MM Socket.cpp

$(IntermediateDirectory)/TcpSocket$(ObjectSuffix): TcpSocket.cpp $(IntermediateDirectory)/TcpSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)TcpSocket.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/TcpSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TcpSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/TcpSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/TcpSocket$(ObjectSuffix).d -MM TcpSocket.cpp

$(IntermediateDirectory)/Thread$(ObjectSuffix): Thread.cpp $(IntermediateDirectory)/Thread$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Thread.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Thread$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Thread$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Thread$(ObjectSuffix) -MF$(IntermediateDirectory)/Thread$(ObjectSuffix).d -MM Thread.cpp

$(IntermediateDirectory)/Utility$(ObjectSuffix): Utility.cpp $(IntermediateDirectory)/Utility$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Utility.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/Utility$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Utility$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Utility$(ObjectSuffix) -MF$(IntermediateDirectory)/Utility$(ObjectSuffix).d -MM Utility.cpp

$(IntermediateDirectory)/UdpSocket$(ObjectSuffix): UdpSocket.cpp $(IntermediateDirectory)/UdpSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)UdpSocket.cpp $(CmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/UdpSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UdpSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/UdpSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/UdpSocket$(ObjectSuffix).d -MM UdpSocket.cpp

##
## Clean
##
clean:
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
	$(RM) $(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/SqliteMgr$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SqliteMgr$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Statements$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Statements$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/ListActor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ListActor$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/CountActor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CountActor$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/SPKCriteria$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SPKCriteria$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/SavableManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SavableManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/FieldDef$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/FieldDef$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/FieldImpl$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/FieldImpl$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/TableDef$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/TableDef$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/TableImpl$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/TableImpl$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Keys$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Keys$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/MPKCriteria$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/MPKCriteria$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/SqliteError$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SqliteError$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Assert$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Assert$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Value$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Value$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Criteria$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Criteria$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Key$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Key$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Base64$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Base64$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Event$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Event$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EventHandler$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EventHandler$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Database$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Database$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Debug$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Debug$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EventTime$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EventTime$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/File$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/File$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/IEventOwner$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/IEventOwner$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Ipv4Address$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Ipv4Address$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Ipv6Address$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Ipv6Address$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Mutex$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Mutex$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/MemFile$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/MemFile$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Lock$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Lock$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Parse$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Parse$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/ResolvServer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ResolvServer$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SmtpdSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/ResolvSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ResolvSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Query$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Query$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/RandomNumber$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/RandomNumber$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/SSLInitializer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SSLInitializer$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/SocketHandler$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SocketHandler$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/StderrLog$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/StderrLog$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/socket_include$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/socket_include$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/StreamSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/StreamSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/StdoutLog$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/StdoutLog$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Socket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Socket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/TcpSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/TcpSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Thread$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Thread$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Utility$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Utility$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/UdpSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/UdpSocket$(ObjectSuffix).d
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*.d

