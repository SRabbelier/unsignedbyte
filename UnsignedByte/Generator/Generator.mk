##
## Auto Generated makefile, please do not edit
##
WorkspaceName=UnsignedByte
WorkspacePath=/home/sverre/code/ub
ProjectName=Generator

## Debug
ifeq ($(type),Debug)
ConfigurationName=Debug
IntermediateDirectory=./Debug
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
OutputFile=../bin/Generator
Preprocessors=
CmpOptions=-g $(Preprocessors)
RcCmpOptions=
LinkOptions=-O0
IncludePath=$(IncludeSwitch). $(IncludeSwitch)../include 
RcIncludePath=
Libs=$(LibrarySwitch)ubresource $(LibrarySwitch)pthread $(LibrarySwitch)dl $(LibrarySwitch)sqlite3 
LibPath=$(LibraryPathSwitch). $(LibraryPathSwitch)../lib 
endif

Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/ClassHeaderGenerator$(ObjectSuffix) $(IntermediateDirectory)/ClassSourceGenerator$(ObjectSuffix) $(IntermediateDirectory)/Generator$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(LinkOptions) $(Objects) $(LibPath) $(Libs)
	@echo Executing Post Build commands ...
	../bin/Generator
	mv db.cpp ../DAL
	mv db.h ../include
	@echo Done

makeDirStep:
	@test -d ./Debug || mkdir ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)main.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(ObjectSuffix).d -MM main.cpp

$(IntermediateDirectory)/ClassHeaderGenerator$(ObjectSuffix): ClassHeaderGenerator.cpp $(IntermediateDirectory)/ClassHeaderGenerator$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)ClassHeaderGenerator.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/ClassHeaderGenerator$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ClassHeaderGenerator$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ClassHeaderGenerator$(ObjectSuffix) -MF$(IntermediateDirectory)/ClassHeaderGenerator$(ObjectSuffix).d -MM ClassHeaderGenerator.cpp

$(IntermediateDirectory)/ClassSourceGenerator$(ObjectSuffix): ClassSourceGenerator.cpp $(IntermediateDirectory)/ClassSourceGenerator$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)ClassSourceGenerator.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/ClassSourceGenerator$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ClassSourceGenerator$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ClassSourceGenerator$(ObjectSuffix) -MF$(IntermediateDirectory)/ClassSourceGenerator$(ObjectSuffix).d -MM ClassSourceGenerator.cpp

$(IntermediateDirectory)/Generator$(ObjectSuffix): Generator.cpp $(IntermediateDirectory)/Generator$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Generator.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Generator$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Generator$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Generator$(ObjectSuffix) -MF$(IntermediateDirectory)/Generator$(ObjectSuffix).d -MM Generator.cpp

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/ClassHeaderGenerator$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ClassHeaderGenerator$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/ClassSourceGenerator$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ClassSourceGenerator$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Generator$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Generator$(ObjectSuffix).d
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*.d

