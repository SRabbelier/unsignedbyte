.PHONY: clean All

All:
	@echo ----------Building project:[ Core - Debug ]----------
	@cd "UnsignedByte/Core" && "/usr/bin/make" -f "Core.mk" type=Debug 
clean:
	@echo ----------Building project:[ Core - Debug ]----------
	@cd "UnsignedByte/Core" && "/usr/bin/make" -f "Core.mk" type=Debug  clean
