# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  GLFW_config = debug
  Glad_config = debug
  ImGui_config = debug
  Nutella_config = debug
  Sandbox_config = debug

else ifeq ($(config),release)
  GLFW_config = release
  Glad_config = release
  ImGui_config = release
  Nutella_config = release
  Sandbox_config = release

else ifeq ($(config),dist)
  GLFW_config = dist
  Glad_config = dist
  ImGui_config = dist
  Nutella_config = dist
  Sandbox_config = dist

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := GLFW Glad ImGui Nutella Sandbox

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

GLFW:
ifneq (,$(GLFW_config))
	@echo "==== Building GLFW ($(GLFW_config)) ===="
	@${MAKE} -C nutella/vendor/GLFW -f Makefile config=$(GLFW_config)
endif

Glad:
ifneq (,$(Glad_config))
	@echo "==== Building Glad ($(Glad_config)) ===="
	@${MAKE} -C nutella/vendor/Glad -f Makefile config=$(Glad_config)
endif

ImGui:
ifneq (,$(ImGui_config))
	@echo "==== Building ImGui ($(ImGui_config)) ===="
	@${MAKE} -C nutella/vendor/imgui -f Makefile config=$(ImGui_config)
endif

Nutella: GLFW Glad ImGui
ifneq (,$(Nutella_config))
	@echo "==== Building Nutella ($(Nutella_config)) ===="
	@${MAKE} -C nutella -f Makefile config=$(Nutella_config)
endif

Sandbox: Nutella
ifneq (,$(Sandbox_config))
	@echo "==== Building Sandbox ($(Sandbox_config)) ===="
	@${MAKE} -C sandbox -f Makefile config=$(Sandbox_config)
endif

clean:
	@${MAKE} --no-print-directory -C nutella/vendor/GLFW -f Makefile clean
	@${MAKE} --no-print-directory -C nutella/vendor/Glad -f Makefile clean
	@${MAKE} --no-print-directory -C nutella/vendor/imgui -f Makefile clean
	@${MAKE} --no-print-directory -C nutella -f Makefile clean
	@${MAKE} --no-print-directory -C sandbox -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo "  dist"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   GLFW"
	@echo "   Glad"
	@echo "   ImGui"
	@echo "   Nutella"
	@echo "   Sandbox"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"