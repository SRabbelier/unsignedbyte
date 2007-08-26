.PHONY: clean All

All:
	@echo ----------Building project:[ Resource - Debug ]----------
	@cd "Resource" && "make" -f "Resource.mk" type=Debug 
	@echo ----------Building project:[ Initializer - Debug ]----------
	@cd "Initializer" && "make" -f "Initializer.mk" type=Debug 
clean:
	@echo ----------Building project:[ Resource - Debug ]----------
	@cd "Resource" && "make" -f "Resource.mk" type=Debug  clean
	@echo ----------Building project:[ Initializer - Debug ]----------
	@cd "Initializer" && "make" -f "Initializer.mk" type=Debug  clean
