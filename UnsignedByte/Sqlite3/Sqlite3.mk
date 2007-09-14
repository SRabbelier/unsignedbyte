##
## Auto Generated makefile, please do not edit
##
WorkspaceName=UnsignedByte
WorkspacePath=/home/sverre/code/ub
ProjectName=Sqlite3

## Debug
ifeq ($(type),Debug)
ConfigurationName=Debug
IntermediateDirectory=./Debug
OutDir=$(IntermediateDirectory)
LinkerName=gcc
ArchiveTool=ar rcu
SharedObjectLinkerName=gcc -shared -fPIC
ObjectSuffix=.o
DebugSwitch=-g 
IncludeSwitch=-I
LibrarySwitch=-l
OutputSwitch=-o 
LibraryPathSwitch=-L
PreprocessorSwitch=-D
SourceSwitch=-c 
CompilerName=gcc
RcCompilerName=windres
OutputFile=../lib/libMySqlite3.a
Preprocessors=
CmpOptions=-g $(Preprocessors)
RcCmpOptions=
LinkOptions=
IncludePath=$(IncludeSwitch). 
RcIncludePath=
Libs=
LibPath=
endif

Objects=$(IntermediateDirectory)/sqlite3$(ObjectSuffix) 

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
$(IntermediateDirectory)/sqlite3$(ObjectSuffix): sqlite3.c $(IntermediateDirectory)/sqlite3$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)sqlite3.c $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/sqlite3$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sqlite3$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/sqlite3$(ObjectSuffix) -MF$(IntermediateDirectory)/sqlite3$(ObjectSuffix).d -MM sqlite3.c

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/sqlite3$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sqlite3$(ObjectSuffix).d
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*.d

