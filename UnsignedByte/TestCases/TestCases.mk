##
## Auto Generated makefile, please do not edit
##
WorkspaceName=UnsignedByte
WorkspacePath=/home/sverre/code/ub
ProjectName=TestCases

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
OutputFile=../bin/TestCase
Preprocessors=
CmpOptions=-g $(Preprocessors)
RcCmpOptions=
LinkOptions=
IncludePath=$(IncludeSwitch). $(IncludeSwitch)../include 
RcIncludePath=
Libs=
LibPath=
endif

Objects=$(IntermediateDirectory)/main$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep PrePreBuild $(Objects)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug || mkdir ./Debug

PrePreBuild: 



PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)main.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(ObjectSuffix).d -MM main.cpp

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix).d
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*.d

