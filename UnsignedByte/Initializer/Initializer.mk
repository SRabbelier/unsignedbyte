##
## Auto Generated makefile, please do not edit
##
WorkspaceName=UnsignedByte
WorkspacePath=/home/sverre/code/ub
ProjectName=Initializer

## Debug
ifeq ($(type),Debug)
ConfigurationName=Debug
IntermediateDirectory=Intermediate
OutDir=$(IntermediateDirectory)
LinkerName=g++
ArchiveTool=ar rcu
SharedObjectLinkerName=g++ -shared -fPIC
ObjectSuffix=.o
DebugSwitch=-g 
IncludeSwitch=-I
LibrarySwitch=-l
OutputSwitch=-o 
LibraryPathSwitch=-L
PreprocessorSwitch=-D
SourceSwitch=-c 
CompilerName=g++
RcCompilerName=windres
OutputFile=../bin/Initialize
Preprocessors=
CmpOptions=-g -Wall $(Preprocessors)
RcCmpOptions=
LinkOptions=-O0
IncludePath=$(IncludeSwitch). $(IncludeSwitch)../include 
RcIncludePath=
Libs=$(LibrarySwitch)pthread $(LibrarySwitch)dl $(LibrarySwitch)sqlite3 $(LibrarySwitch)ubdal $(LibrarySwitch)ubresource 
LibPath=$(LibraryPathSwitch). $(LibraryPathSwitch)../lib 
endif

Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/Initializer$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep PrePreBuild $(Objects)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(LinkOptions) $(Objects) $(LibPath) $(Libs)

makeDirStep:
	@test -d Intermediate || mkdir Intermediate

PrePreBuild: 



PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)main.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(ObjectSuffix).d -MM main.cpp

$(IntermediateDirectory)/Initializer$(ObjectSuffix): Initializer.cpp $(IntermediateDirectory)/Initializer$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Initializer.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Initializer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Initializer$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Initializer$(ObjectSuffix) -MF$(IntermediateDirectory)/Initializer$(ObjectSuffix).d -MM Initializer.cpp

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Initializer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Initializer$(ObjectSuffix).d
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*.d

