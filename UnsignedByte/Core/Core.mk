##
## Auto Generated makefile, please do not edit
##
WorkspaceName=UnsignedByte
WorkspacePath=/home/sverre/code/ub
ProjectName=Core

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
OutputFile=../bin/UnsignedByte
Preprocessors=
CmpOptions=-g -Wall $(Preprocessors)
RcCmpOptions=
LinkOptions=
IncludePath=$(IncludeSwitch). $(IncludeSwitch)../include 
RcIncludePath=
Libs=$(LibrarySwitch)pthread $(LibrarySwitch)dl $(LibrarySwitch)ubdal $(LibrarySwitch)ubresource $(LibrarySwitch)MySqlite3 
LibPath=$(LibraryPathSwitch). $(LibraryPathSwitch)../lib 
endif

Objects=$(IntermediateDirectory)/Account$(ObjectSuffix) $(IntermediateDirectory)/Area$(ObjectSuffix) $(IntermediateDirectory)/Character$(ObjectSuffix) $(IntermediateDirectory)/Colour$(ObjectSuffix) $(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/MCharacter$(ObjectSuffix) $(IntermediateDirectory)/PCharacter$(ObjectSuffix) $(IntermediateDirectory)/Race$(ObjectSuffix) $(IntermediateDirectory)/Room$(ObjectSuffix) $(IntermediateDirectory)/Sector$(ObjectSuffix) \
	$(IntermediateDirectory)/UBHandler$(ObjectSuffix) $(IntermediateDirectory)/UBSocket$(ObjectSuffix) $(IntermediateDirectory)/SQLSocket$(ObjectSuffix) $(IntermediateDirectory)/Command$(ObjectSuffix) $(IntermediateDirectory)/GrantGroup$(ObjectSuffix) $(IntermediateDirectory)/Permission$(ObjectSuffix) $(IntermediateDirectory)/Chunk$(ObjectSuffix) $(IntermediateDirectory)/chunkimporter$(ObjectSuffix) $(IntermediateDirectory)/Detail$(ObjectSuffix) $(IntermediateDirectory)/Exit$(ObjectSuffix) \
	$(IntermediateDirectory)/EditorOLC$(ObjectSuffix) $(IntermediateDirectory)/Editor$(ObjectSuffix) $(IntermediateDirectory)/EditorPermission$(ObjectSuffix) $(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix) $(IntermediateDirectory)/EditorString$(ObjectSuffix) $(IntermediateDirectory)/EditorCommand$(ObjectSuffix) $(IntermediateDirectory)/EditorScript$(ObjectSuffix) $(IntermediateDirectory)/EditorSector$(ObjectSuffix) $(IntermediateDirectory)/EditorRoom$(ObjectSuffix) $(IntermediateDirectory)/EditorPlaying$(ObjectSuffix) \
	$(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix) $(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix) $(IntermediateDirectory)/EditorAccount$(ObjectSuffix) $(IntermediateDirectory)/EditorMobile$(ObjectSuffix) $(IntermediateDirectory)/EditorArea$(ObjectSuffix) $(IntermediateDirectory)/EditorColour$(ObjectSuffix) $(IntermediateDirectory)/OLCEditor$(ObjectSuffix) $(IntermediateDirectory)/EditorAccountLogin$(ObjectSuffix) $(IntermediateDirectory)/EditorOOC$(ObjectSuffix) $(IntermediateDirectory)/EditorChunk$(ObjectSuffix) \
	$(IntermediateDirectory)/EditorBool$(ObjectSuffix) $(IntermediateDirectory)/EditorDetail$(ObjectSuffix) $(IntermediateDirectory)/EditorRace$(ObjectSuffix) $(IntermediateDirectory)/AccountManager$(ObjectSuffix) $(IntermediateDirectory)/AreaManager$(ObjectSuffix) $(IntermediateDirectory)/CharacterManager$(ObjectSuffix) $(IntermediateDirectory)/ColourManager$(ObjectSuffix) $(IntermediateDirectory)/CommandManager$(ObjectSuffix) $(IntermediateDirectory)/GrantGroupManager$(ObjectSuffix) $(IntermediateDirectory)/MCharacterManager$(ObjectSuffix) \
	$(IntermediateDirectory)/PCharacterManager$(ObjectSuffix) $(IntermediateDirectory)/PermissionManager$(ObjectSuffix) $(IntermediateDirectory)/RaceManager$(ObjectSuffix) $(IntermediateDirectory)/RoomManager$(ObjectSuffix) $(IntermediateDirectory)/SectorManager$(ObjectSuffix) $(IntermediateDirectory)/ChunkManager$(ObjectSuffix) $(IntermediateDirectory)/DetailManager$(ObjectSuffix) $(IntermediateDirectory)/ExitManager$(ObjectSuffix) 

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
$(IntermediateDirectory)/Account$(ObjectSuffix): Account.cpp $(IntermediateDirectory)/Account$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Account.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Account$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Account$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Account$(ObjectSuffix) -MF$(IntermediateDirectory)/Account$(ObjectSuffix).d -MM Account.cpp

$(IntermediateDirectory)/Area$(ObjectSuffix): Area.cpp $(IntermediateDirectory)/Area$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Area.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Area$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Area$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Area$(ObjectSuffix) -MF$(IntermediateDirectory)/Area$(ObjectSuffix).d -MM Area.cpp

$(IntermediateDirectory)/Character$(ObjectSuffix): Character.cpp $(IntermediateDirectory)/Character$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Character.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Character$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Character$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Character$(ObjectSuffix) -MF$(IntermediateDirectory)/Character$(ObjectSuffix).d -MM Character.cpp

$(IntermediateDirectory)/Colour$(ObjectSuffix): Colour.cpp $(IntermediateDirectory)/Colour$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Colour.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Colour$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Colour$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Colour$(ObjectSuffix) -MF$(IntermediateDirectory)/Colour$(ObjectSuffix).d -MM Colour.cpp

$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)main.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(ObjectSuffix).d -MM main.cpp

$(IntermediateDirectory)/MCharacter$(ObjectSuffix): MCharacter.cpp $(IntermediateDirectory)/MCharacter$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)MCharacter.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/MCharacter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MCharacter$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/MCharacter$(ObjectSuffix) -MF$(IntermediateDirectory)/MCharacter$(ObjectSuffix).d -MM MCharacter.cpp

$(IntermediateDirectory)/PCharacter$(ObjectSuffix): PCharacter.cpp $(IntermediateDirectory)/PCharacter$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)PCharacter.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/PCharacter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PCharacter$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/PCharacter$(ObjectSuffix) -MF$(IntermediateDirectory)/PCharacter$(ObjectSuffix).d -MM PCharacter.cpp

$(IntermediateDirectory)/Race$(ObjectSuffix): Race.cpp $(IntermediateDirectory)/Race$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Race.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Race$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Race$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Race$(ObjectSuffix) -MF$(IntermediateDirectory)/Race$(ObjectSuffix).d -MM Race.cpp

$(IntermediateDirectory)/Room$(ObjectSuffix): Room.cpp $(IntermediateDirectory)/Room$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Room.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Room$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Room$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Room$(ObjectSuffix) -MF$(IntermediateDirectory)/Room$(ObjectSuffix).d -MM Room.cpp

$(IntermediateDirectory)/Sector$(ObjectSuffix): Sector.cpp $(IntermediateDirectory)/Sector$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Sector.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Sector$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Sector$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Sector$(ObjectSuffix) -MF$(IntermediateDirectory)/Sector$(ObjectSuffix).d -MM Sector.cpp

$(IntermediateDirectory)/UBHandler$(ObjectSuffix): UBHandler.cpp $(IntermediateDirectory)/UBHandler$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)UBHandler.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/UBHandler$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UBHandler$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/UBHandler$(ObjectSuffix) -MF$(IntermediateDirectory)/UBHandler$(ObjectSuffix).d -MM UBHandler.cpp

$(IntermediateDirectory)/UBSocket$(ObjectSuffix): UBSocket.cpp $(IntermediateDirectory)/UBSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)UBSocket.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/UBSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UBSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/UBSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/UBSocket$(ObjectSuffix).d -MM UBSocket.cpp

$(IntermediateDirectory)/SQLSocket$(ObjectSuffix): SQLSocket.cpp $(IntermediateDirectory)/SQLSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)SQLSocket.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/SQLSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SQLSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SQLSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/SQLSocket$(ObjectSuffix).d -MM SQLSocket.cpp

$(IntermediateDirectory)/Command$(ObjectSuffix): Command.cpp $(IntermediateDirectory)/Command$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Command.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Command$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Command$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Command$(ObjectSuffix) -MF$(IntermediateDirectory)/Command$(ObjectSuffix).d -MM Command.cpp

$(IntermediateDirectory)/GrantGroup$(ObjectSuffix): GrantGroup.cpp $(IntermediateDirectory)/GrantGroup$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)GrantGroup.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/GrantGroup$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GrantGroup$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/GrantGroup$(ObjectSuffix) -MF$(IntermediateDirectory)/GrantGroup$(ObjectSuffix).d -MM GrantGroup.cpp

$(IntermediateDirectory)/Permission$(ObjectSuffix): Permission.cpp $(IntermediateDirectory)/Permission$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Permission.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Permission$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Permission$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Permission$(ObjectSuffix) -MF$(IntermediateDirectory)/Permission$(ObjectSuffix).d -MM Permission.cpp

$(IntermediateDirectory)/Chunk$(ObjectSuffix): Chunk.cpp $(IntermediateDirectory)/Chunk$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Chunk.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Chunk$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Chunk$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Chunk$(ObjectSuffix) -MF$(IntermediateDirectory)/Chunk$(ObjectSuffix).d -MM Chunk.cpp

$(IntermediateDirectory)/chunkimporter$(ObjectSuffix): chunkimporter.cpp $(IntermediateDirectory)/chunkimporter$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)chunkimporter.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/chunkimporter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/chunkimporter$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/chunkimporter$(ObjectSuffix) -MF$(IntermediateDirectory)/chunkimporter$(ObjectSuffix).d -MM chunkimporter.cpp

$(IntermediateDirectory)/Detail$(ObjectSuffix): Detail.cpp $(IntermediateDirectory)/Detail$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Detail.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Detail$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Detail$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Detail$(ObjectSuffix) -MF$(IntermediateDirectory)/Detail$(ObjectSuffix).d -MM Detail.cpp

$(IntermediateDirectory)/Exit$(ObjectSuffix): Exit.cpp $(IntermediateDirectory)/Exit$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Exit.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Exit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Exit$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Exit$(ObjectSuffix) -MF$(IntermediateDirectory)/Exit$(ObjectSuffix).d -MM Exit.cpp

$(IntermediateDirectory)/EditorOLC$(ObjectSuffix): EditorOLC.cpp $(IntermediateDirectory)/EditorOLC$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorOLC.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorOLC$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorOLC$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorOLC$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorOLC$(ObjectSuffix).d -MM EditorOLC.cpp

$(IntermediateDirectory)/Editor$(ObjectSuffix): Editor.cpp $(IntermediateDirectory)/Editor$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)Editor.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/Editor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Editor$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Editor$(ObjectSuffix) -MF$(IntermediateDirectory)/Editor$(ObjectSuffix).d -MM Editor.cpp

$(IntermediateDirectory)/EditorPermission$(ObjectSuffix): EditorPermission.cpp $(IntermediateDirectory)/EditorPermission$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorPermission.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorPermission$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorPermission$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorPermission$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorPermission$(ObjectSuffix).d -MM EditorPermission.cpp

$(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix): EditorGrantGroup.cpp $(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorGrantGroup.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix).d -MM EditorGrantGroup.cpp

$(IntermediateDirectory)/EditorString$(ObjectSuffix): EditorString.cpp $(IntermediateDirectory)/EditorString$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorString.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorString$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorString$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorString$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorString$(ObjectSuffix).d -MM EditorString.cpp

$(IntermediateDirectory)/EditorCommand$(ObjectSuffix): EditorCommand.cpp $(IntermediateDirectory)/EditorCommand$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorCommand.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorCommand$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorCommand$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorCommand$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorCommand$(ObjectSuffix).d -MM EditorCommand.cpp

$(IntermediateDirectory)/EditorScript$(ObjectSuffix): EditorScript.cpp $(IntermediateDirectory)/EditorScript$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorScript.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorScript$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorScript$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorScript$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorScript$(ObjectSuffix).d -MM EditorScript.cpp

$(IntermediateDirectory)/EditorSector$(ObjectSuffix): EditorSector.cpp $(IntermediateDirectory)/EditorSector$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorSector.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorSector$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorSector$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorSector$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorSector$(ObjectSuffix).d -MM EditorSector.cpp

$(IntermediateDirectory)/EditorRoom$(ObjectSuffix): EditorRoom.cpp $(IntermediateDirectory)/EditorRoom$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorRoom.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorRoom$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorRoom$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorRoom$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorRoom$(ObjectSuffix).d -MM EditorRoom.cpp

$(IntermediateDirectory)/EditorPlaying$(ObjectSuffix): EditorPlaying.cpp $(IntermediateDirectory)/EditorPlaying$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorPlaying.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorPlaying$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorPlaying$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorPlaying$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorPlaying$(ObjectSuffix).d -MM EditorPlaying.cpp

$(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix): EditorNewCharacter.cpp $(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorNewCharacter.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix).d -MM EditorNewCharacter.cpp

$(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix): EditorNewAccount.cpp $(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorNewAccount.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix).d -MM EditorNewAccount.cpp

$(IntermediateDirectory)/EditorAccount$(ObjectSuffix): EditorAccount.cpp $(IntermediateDirectory)/EditorAccount$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorAccount.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorAccount$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorAccount$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorAccount$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorAccount$(ObjectSuffix).d -MM EditorAccount.cpp

$(IntermediateDirectory)/EditorMobile$(ObjectSuffix): EditorMobile.cpp $(IntermediateDirectory)/EditorMobile$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorMobile.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorMobile$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorMobile$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorMobile$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorMobile$(ObjectSuffix).d -MM EditorMobile.cpp

$(IntermediateDirectory)/EditorArea$(ObjectSuffix): EditorArea.cpp $(IntermediateDirectory)/EditorArea$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorArea.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorArea$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorArea$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorArea$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorArea$(ObjectSuffix).d -MM EditorArea.cpp

$(IntermediateDirectory)/EditorColour$(ObjectSuffix): EditorColour.cpp $(IntermediateDirectory)/EditorColour$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorColour.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorColour$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorColour$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorColour$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorColour$(ObjectSuffix).d -MM EditorColour.cpp

$(IntermediateDirectory)/OLCEditor$(ObjectSuffix): OLCEditor.cpp $(IntermediateDirectory)/OLCEditor$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)OLCEditor.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/OLCEditor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OLCEditor$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/OLCEditor$(ObjectSuffix) -MF$(IntermediateDirectory)/OLCEditor$(ObjectSuffix).d -MM OLCEditor.cpp

$(IntermediateDirectory)/EditorAccountLogin$(ObjectSuffix): EditorAccountLogin.cpp $(IntermediateDirectory)/EditorAccountLogin$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorAccountLogin.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorAccountLogin$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorAccountLogin$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorAccountLogin$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorAccountLogin$(ObjectSuffix).d -MM EditorAccountLogin.cpp

$(IntermediateDirectory)/EditorOOC$(ObjectSuffix): EditorOOC.cpp $(IntermediateDirectory)/EditorOOC$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorOOC.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorOOC$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorOOC$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorOOC$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorOOC$(ObjectSuffix).d -MM EditorOOC.cpp

$(IntermediateDirectory)/EditorChunk$(ObjectSuffix): EditorChunk.cpp $(IntermediateDirectory)/EditorChunk$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorChunk.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorChunk$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorChunk$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorChunk$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorChunk$(ObjectSuffix).d -MM EditorChunk.cpp

$(IntermediateDirectory)/EditorBool$(ObjectSuffix): EditorBool.cpp $(IntermediateDirectory)/EditorBool$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorBool.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorBool$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorBool$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorBool$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorBool$(ObjectSuffix).d -MM EditorBool.cpp

$(IntermediateDirectory)/EditorDetail$(ObjectSuffix): EditorDetail.cpp $(IntermediateDirectory)/EditorDetail$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorDetail.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorDetail$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorDetail$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorDetail$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorDetail$(ObjectSuffix).d -MM EditorDetail.cpp

$(IntermediateDirectory)/EditorRace$(ObjectSuffix): EditorRace.cpp $(IntermediateDirectory)/EditorRace$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)EditorRace.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/EditorRace$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorRace$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorRace$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorRace$(ObjectSuffix).d -MM EditorRace.cpp

$(IntermediateDirectory)/AccountManager$(ObjectSuffix): AccountManager.cpp $(IntermediateDirectory)/AccountManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)AccountManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/AccountManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AccountManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/AccountManager$(ObjectSuffix) -MF$(IntermediateDirectory)/AccountManager$(ObjectSuffix).d -MM AccountManager.cpp

$(IntermediateDirectory)/AreaManager$(ObjectSuffix): AreaManager.cpp $(IntermediateDirectory)/AreaManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)AreaManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/AreaManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AreaManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/AreaManager$(ObjectSuffix) -MF$(IntermediateDirectory)/AreaManager$(ObjectSuffix).d -MM AreaManager.cpp

$(IntermediateDirectory)/CharacterManager$(ObjectSuffix): CharacterManager.cpp $(IntermediateDirectory)/CharacterManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)CharacterManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/CharacterManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CharacterManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/CharacterManager$(ObjectSuffix) -MF$(IntermediateDirectory)/CharacterManager$(ObjectSuffix).d -MM CharacterManager.cpp

$(IntermediateDirectory)/ColourManager$(ObjectSuffix): ColourManager.cpp $(IntermediateDirectory)/ColourManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)ColourManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/ColourManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ColourManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ColourManager$(ObjectSuffix) -MF$(IntermediateDirectory)/ColourManager$(ObjectSuffix).d -MM ColourManager.cpp

$(IntermediateDirectory)/CommandManager$(ObjectSuffix): CommandManager.cpp $(IntermediateDirectory)/CommandManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)CommandManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/CommandManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CommandManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/CommandManager$(ObjectSuffix) -MF$(IntermediateDirectory)/CommandManager$(ObjectSuffix).d -MM CommandManager.cpp

$(IntermediateDirectory)/GrantGroupManager$(ObjectSuffix): GrantGroupManager.cpp $(IntermediateDirectory)/GrantGroupManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)GrantGroupManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/GrantGroupManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GrantGroupManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/GrantGroupManager$(ObjectSuffix) -MF$(IntermediateDirectory)/GrantGroupManager$(ObjectSuffix).d -MM GrantGroupManager.cpp

$(IntermediateDirectory)/MCharacterManager$(ObjectSuffix): MCharacterManager.cpp $(IntermediateDirectory)/MCharacterManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)MCharacterManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/MCharacterManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MCharacterManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/MCharacterManager$(ObjectSuffix) -MF$(IntermediateDirectory)/MCharacterManager$(ObjectSuffix).d -MM MCharacterManager.cpp

$(IntermediateDirectory)/PCharacterManager$(ObjectSuffix): PCharacterManager.cpp $(IntermediateDirectory)/PCharacterManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)PCharacterManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/PCharacterManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PCharacterManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/PCharacterManager$(ObjectSuffix) -MF$(IntermediateDirectory)/PCharacterManager$(ObjectSuffix).d -MM PCharacterManager.cpp

$(IntermediateDirectory)/PermissionManager$(ObjectSuffix): PermissionManager.cpp $(IntermediateDirectory)/PermissionManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)PermissionManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/PermissionManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PermissionManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/PermissionManager$(ObjectSuffix) -MF$(IntermediateDirectory)/PermissionManager$(ObjectSuffix).d -MM PermissionManager.cpp

$(IntermediateDirectory)/RaceManager$(ObjectSuffix): RaceManager.cpp $(IntermediateDirectory)/RaceManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)RaceManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/RaceManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/RaceManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/RaceManager$(ObjectSuffix) -MF$(IntermediateDirectory)/RaceManager$(ObjectSuffix).d -MM RaceManager.cpp

$(IntermediateDirectory)/RoomManager$(ObjectSuffix): RoomManager.cpp $(IntermediateDirectory)/RoomManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)RoomManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/RoomManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/RoomManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/RoomManager$(ObjectSuffix) -MF$(IntermediateDirectory)/RoomManager$(ObjectSuffix).d -MM RoomManager.cpp

$(IntermediateDirectory)/SectorManager$(ObjectSuffix): SectorManager.cpp $(IntermediateDirectory)/SectorManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)SectorManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/SectorManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SectorManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SectorManager$(ObjectSuffix) -MF$(IntermediateDirectory)/SectorManager$(ObjectSuffix).d -MM SectorManager.cpp

$(IntermediateDirectory)/ChunkManager$(ObjectSuffix): ChunkManager.cpp $(IntermediateDirectory)/ChunkManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)ChunkManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/ChunkManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ChunkManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ChunkManager$(ObjectSuffix) -MF$(IntermediateDirectory)/ChunkManager$(ObjectSuffix).d -MM ChunkManager.cpp

$(IntermediateDirectory)/DetailManager$(ObjectSuffix): DetailManager.cpp $(IntermediateDirectory)/DetailManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)DetailManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/DetailManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DetailManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/DetailManager$(ObjectSuffix) -MF$(IntermediateDirectory)/DetailManager$(ObjectSuffix).d -MM DetailManager.cpp

$(IntermediateDirectory)/ExitManager$(ObjectSuffix): ExitManager.cpp $(IntermediateDirectory)/ExitManager$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch)ExitManager.cpp $(CmpOptions)   $(OutputSwitch)$(IntermediateDirectory)/ExitManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ExitManager$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ExitManager$(ObjectSuffix) -MF$(IntermediateDirectory)/ExitManager$(ObjectSuffix).d -MM ExitManager.cpp

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Account$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Account$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Area$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Area$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Character$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Character$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Colour$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Colour$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/MCharacter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/MCharacter$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/PCharacter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/PCharacter$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Race$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Race$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Room$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Room$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Sector$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Sector$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/UBHandler$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/UBHandler$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/UBSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/UBSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/SQLSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SQLSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Command$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Command$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/GrantGroup$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GrantGroup$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Permission$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Permission$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Chunk$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Chunk$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/chunkimporter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/chunkimporter$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Detail$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Detail$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Exit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Exit$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorOLC$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorOLC$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Editor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Editor$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorPermission$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorPermission$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorString$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorString$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorCommand$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorCommand$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorScript$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorScript$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorSector$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorSector$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorRoom$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorRoom$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorPlaying$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorPlaying$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorAccount$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorAccount$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorMobile$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorMobile$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorArea$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorArea$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorColour$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorColour$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/OLCEditor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OLCEditor$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorAccountLogin$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorAccountLogin$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorOOC$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorOOC$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorChunk$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorChunk$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorBool$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorBool$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorDetail$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorDetail$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorRace$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorRace$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/AccountManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/AccountManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/AreaManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/AreaManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/CharacterManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CharacterManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/ColourManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ColourManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/CommandManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CommandManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/GrantGroupManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GrantGroupManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/MCharacterManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/MCharacterManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/PCharacterManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/PCharacterManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/PermissionManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/PermissionManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/RaceManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/RaceManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/RoomManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/RoomManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/SectorManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SectorManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/ChunkManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ChunkManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/DetailManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/DetailManager$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/ExitManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ExitManager$(ObjectSuffix).d
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*.d

