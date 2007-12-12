.PHONY: clean All

All:
	@echo ----------Building project:[ Resource - Debug ]----------
	@cd "UnsignedByte/Resource" && "/usr/bin/make" -f "Resource.mk" type=Debug 
	@echo ----------Building project:[ Core - Debug ]----------
	@cd "UnsignedByte/Core" && "/usr/bin/make" -f "Core.mk" type=Debug 
clean:
	@echo ----------Building project:[ Resource - Debug ]----------
	@cd "UnsignedByte/Resource" && "/usr/bin/make" -f "Resource.mk" type=Debug  clean
	@echo ----------Building project:[ Core - Debug ]----------
	@cd "UnsignedByte/Core" && "/usr/bin/make" -f "Core.mk" type=Debug  clean
