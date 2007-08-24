##
## Auto Generated makefile, please do not edit
##
WorkspaceName=MUD Development
WorkspacePath=/home/sverre/code/UBSVN/Trunk
ProjectName=TestCase

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
OutputFile=libtestcase.a
Preprocessors=
CmpOptions=-g $(Preprocessors)
RcCmpOptions=
LinkOptions=-O0
IncludePath=$(IncludeSwitch). $(IncludeSwitch)./include 
RcIncludePath=
Libs=
LibPath=$(LibraryPathSwitch). $(LibraryPathSwitch)Debug 
endif

Objects=$(IntermediateDirectory)/hp$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep PreBuild $(Objects)
	$(SharedObjectLinkerName) $(OutputSwitch) $(OutputFile) $(LinkOptions) $(Objects) $(LibPath) $(Libs)

makeDirStep:
	@test -d ./Debug || mkdir ./Debug

PreBuild:
	@echo Executing Pre Build commands ...
	./Initialize
	@echo Done


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

