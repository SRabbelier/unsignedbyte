.PHONY: clean All

All:
	@echo ----------Building project:[ Resource - Debug ]----------
	@cd "UnsignedByte/Resource" && "make" -f "Resource.mk" type=Debug 
	@echo ----------Building project:[ Generator - Debug ]----------
	@cd "UnsignedByte/Generator" && "make" -f "Generator.mk" type=Debug 
	@echo ----------Building project:[ DAL - Debug ]----------
	@cd "UnsignedByte/DAL" && "make" -f "DAL.mk" type=Debug 
	@echo ----------Building project:[ Initializer - Debug ]----------
	@cd "UnsignedByte/Initializer" && "make" -f "Initializer.mk" type=Debug 
clean:
	@echo ----------Building project:[ Resource - Debug ]----------
	@cd "UnsignedByte/Resource" && "make" -f "Resource.mk" type=Debug  clean
	@echo ----------Building project:[ Generator - Debug ]----------
	@cd "UnsignedByte/Generator" && "make" -f "Generator.mk" type=Debug  clean
	@echo ----------Building project:[ DAL - Debug ]----------
	@cd "UnsignedByte/DAL" && "make" -f "DAL.mk" type=Debug  clean
	@echo ----------Building project:[ Initializer - Debug ]----------
	@cd "UnsignedByte/Initializer" && "make" -f "Initializer.mk" type=Debug  clean
