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
OutputFile=../lib/libubdal.a
Preprocessors=
CmpOptions=-g $(Preprocessors)
RcCmpOptions=
LinkOptions=-O0
IncludePath=$(IncludeSwitch). $(IncludeSwitch)../include 
RcIncludePath=
Libs=
LibPath=$(LibraryPathSwitch). 
endif

Objects=$(IntermediateDirectory)/hp$(ObjectSuffix) 

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
$(IntermediateDirectory)/hp$(ObjectSuffix): hp.cpp $(IntermediateDirectory)/hp$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) hp.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/hp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/hp$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/hp$(ObjectSuffix) -MF$(IntermediateDirectory)/hp$(ObjectSuffix).d -MM hp.cpp

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/hp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/hp$(ObjectSuffix).d
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*.d

