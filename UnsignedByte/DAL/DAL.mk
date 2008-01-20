##
## Auto Generated makefile, please do not edit
##
WorkspaceName=UnsignedByte
WorkspacePath=/home/sverre/code/ub
ProjectName=DAL

## Debug
ifeq ($(type),Debug)
ConfigurationName=Debug
IntermediateDirectory=./Debug
OutDir=$(IntermediateDirectory)
LinkerName=g++
ArchiveTool=ar rcu
SharedObjectLinkerName=g++ -shared -fPIC
ObjectSuffix=.o
DebugSwitch=-gstabs 
IncludeSwitch=-I
LibrarySwitch=-l
OutputSwitch=-o 
LibraryPathSwitch=-L
PreprocessorSwitch=-D
SourceSwitch=-c 
CompilerName=g++
RcCompilerName=windres
OutputFile=../lib/libubdal.a
Preprocessors=
CmpOptions=-g -Wall $(Preprocessors)
RcCmpOptions=
LinkOptions=-O0
IncludePath=$(IncludeSwitch). $(IncludeSwitch)../include 
RcIncludePath=
Libs=
LibPath=$(LibraryPathSwitch). 
endif

Objects=$(IntermediateDirectory)/db$(ObjectSuffix) $(IntermediateDirectory)/TableImpls$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile):  $(Objects)
	$(ArchiveTool) $(OutputFile) $(Objects)

./Debug:
	@test -d ./Debug || mkdir ./Debug


PreBuild:


##
## Objects
##
$(IntermediateDirectory)/db$(ObjectSuffix): db.cpp $(IntermediateDirectory)/db$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)db.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/db$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/db$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/db$(ObjectSuffix) -MF$(IntermediateDirectory)/db$(ObjectSuffix).d -MM db.cpp

$(IntermediateDirectory)/TableImpls$(ObjectSuffix): TableImpls.cpp $(IntermediateDirectory)/TableImpls$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)TableImpls.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/TableImpls$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TableImpls$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/TableImpls$(ObjectSuffix) -MF$(IntermediateDirectory)/TableImpls$(ObjectSuffix).d -MM TableImpls.cpp

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/db$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/db$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/TableImpls$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/TableImpls$(ObjectSuffix).d
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*.d

