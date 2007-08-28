.PHONY: clean All

All:
	@echo ----------Building project:[ Initializer - Debug ]----------
	@cd "Initializer" && "make" -f "Initializer.mk" type=Debug 
	@echo ----------Building project:[ TestCase - Debug ]----------
	@"make" -f "TestCase.mk" type=Debug 
clean:
	@echo ----------Building project:[ Initializer - Debug ]----------
	@cd "Initializer" && "make" -f "Initializer.mk" type=Debug  clean
	@echo ----------Building project:[ TestCase - Debug ]----------
	@"make" -f "TestCase.mk" type=Debug  clean
