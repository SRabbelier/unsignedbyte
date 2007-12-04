.PHONY: clean All

All:
	@echo ----------Building project:[ Resource - Debug ]----------
	@cd "UnsignedByte/Resource" && "/usr/bin/make" -f "Resource.mk" type=Debug 
	@echo ----------Building project:[ Generator - Debug ]----------
	@cd "UnsignedByte/Generator" && "/usr/bin/make" -f "Generator.mk" type=Debug 
	@echo ----------Building project:[ DAL - Debug ]----------
	@cd "UnsignedByte/DAL" && "/usr/bin/make" -f "DAL.mk" type=Debug 
	@echo ----------Building project:[ Initializer - Debug ]----------
	@cd "UnsignedByte/Initializer" && "/usr/bin/make" -f "Initializer.mk" type=Debug 
clean:
	@echo ----------Building project:[ Resource - Debug ]----------
	@cd "UnsignedByte/Resource" && "/usr/bin/make" -f "Resource.mk" type=Debug  clean
	@echo ----------Building project:[ Generator - Debug ]----------
	@cd "UnsignedByte/Generator" && "/usr/bin/make" -f "Generator.mk" type=Debug  clean
	@echo ----------Building project:[ DAL - Debug ]----------
	@cd "UnsignedByte/DAL" && "/usr/bin/make" -f "DAL.mk" type=Debug  clean
	@echo ----------Building project:[ Initializer - Debug ]----------
	@cd "UnsignedByte/Initializer" && "/usr/bin/make" -f "Initializer.mk" type=Debug  clean
