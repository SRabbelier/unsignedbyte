##
## Auto Generated makefile, please do not edit
##
WorkspaceName=MUD Development
WorkspacePath=/home/sverre/code/UBSVN/Trunk

## ReleaseANSI
ifeq ($(type), ReleaseANSI)
LinkerName=gcc
ArchiveTool=ar rcu
SharedObjectLinkerName=gcc -shared
ObjectSuffix=.o
DebugSwitch=-g
IncludeSwitch=-I
LibrarySwitch=-l
OutputSwitch=-o
LibraryPathSwitch=-L
PreprocessorSwitch=-D
SourceSwitch=-c
CompilerName=gcc
RcCompilerName=
OutputFile=../libmysqlite3.a
IntermediateDirectory=./Release
Preprocessors=
CmpOptions=-O2 $(Preprocessors)
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

$(IntermediateDirectory):
	@test -d ./Release || mkdir ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/sqlite3$(ObjectSuffix): sqlite3.c $(IntermediateDirectory)/sqlite3$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) sqlite3.c $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/sqlite3$(ObjectSuffix) $(IncludePath)
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

