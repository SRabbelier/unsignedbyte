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
IncludePath=$(IncludeSwitch). $(IncludeSwitch)../include $(IncludeSwitch)../Core 
RcIncludePath=
Libs=$(LibrarySwitch)ubdal $(LibrarySwitch)ubresource $(LibrarySwitch)sqlite3 
LibPath=$(LibraryPathSwitch)../lib 
endif

Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/chunkimporter$(ObjectSuffix) $(IntermediateDirectory)/Chunk$(ObjectSuffix) $(IntermediateDirectory)/ChunkManager$(ObjectSuffix) $(IntermediateDirectory)/Detail$(ObjectSuffix) $(IntermediateDirectory)/DetailManager$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep  $(Objects)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

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

$(IntermediateDirectory)/chunkimporter$(ObjectSuffix): ../Core/chunkimporter.cpp $(IntermediateDirectory)/chunkimporter$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)../Core/chunkimporter.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/chunkimporter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/chunkimporter$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/chunkimporter$(ObjectSuffix) -MF$(IntermediateDirectory)/chunkimporter$(ObjectSuffix).d -MM ../Core/chunkimporter.cpp

$(IntermediateDirectory)/Chunk$(ObjectSuffix): ../Core/Chunk.cpp $(IntermediateDirectory)/Chunk$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)../Core/Chunk.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Chunk$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Chunk$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Chunk$(ObjectSuffix) -MF$(IntermediateDirectory)/Chunk$(ObjectSuffix).d -MM ../Core/Chunk.cpp

$(IntermediateDirectory)/ChunkManager$(ObjectSuffix): ../Core/ChunkManager.cpp $(IntermediateDirectory)/ChunkManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)../Core/ChunkManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/ChunkManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ChunkManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ChunkManager$(ObjectSuffix) -MF$(IntermediateDirectory)/ChunkManager$(ObjectSuffix).d -MM ../Core/ChunkManager.cpp

$(IntermediateDirectory)/Detail$(ObjectSuffix): ../Core/Detail.cpp $(IntermediateDirectory)/Detail$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)../Core/Detail.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Detail$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Detail$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Detail$(ObjectSuffix) -MF$(IntermediateDirectory)/Detail$(ObjectSuffix).d -MM ../Core/Detail.cpp

$(IntermediateDirectory)/DetailManager$(ObjectSuffix): ../Core/DetailManager.cpp $(IntermediateDirectory)/DetailManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)../Core/DetailManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/DetailManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DetailManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/DetailManager$(ObjectSuffix) -MF$(IntermediateDirectory)/DetailManager$(ObjectSuffix).d -MM ../Core/DetailManager.cpp

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/chunkimporter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/chunkimporter$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Chunk$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Chunk$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/ChunkManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ChunkManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Detail$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Detail$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/DetailManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/DetailManager$(ObjectSuffix).d
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*.d

