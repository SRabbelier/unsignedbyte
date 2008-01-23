.PHONY: clean All

All:
	@echo ----------Building project:[ Resource - Debug ]----------
	@cd "UnsignedByte/Resource" && "$(MAKE)" -f "Resource.mk" type=Debug 
	@echo ----------Building project:[ DAL - Debug ]----------
	@cd "UnsignedByte/DAL" && "$(MAKE)" -f "DAL.mk" type=Debug 
	@echo ----------Building project:[ Core - Debug ]----------
	@cd "UnsignedByte/Core" && "$(MAKE)" -f "Core.mk" type=Debug 
clean:
	@echo ----------Building project:[ Resource - Debug ]----------
	@cd "UnsignedByte/Resource" && "$(MAKE)" -f "Resource.mk" type=Debug  clean
	@echo ----------Building project:[ DAL - Debug ]----------
	@cd "UnsignedByte/DAL" && "$(MAKE)" -f "DAL.mk" type=Debug  clean
	@echo ----------Building project:[ Core - Debug ]----------
	@cd "UnsignedByte/Core" && "$(MAKE)" -f "Core.mk" type=Debug  clean
