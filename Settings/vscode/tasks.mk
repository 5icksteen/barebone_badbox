include Settings/platform.mk

define TASKS
{
    "version": "2.0.0",
    "type": "shell",
    "echoCommand": true,
    "tasks": [
        {
            "label": "Clean & Build",
            "command": "make",
            "args": [
                "clean;",
                "make",
                "-j$(NPROCS)"
            ],
            "group": "build",
            "problemMatcher": []
        },
        {
            "label": "Clean & Build & Flash",
            "command": "make",
            "args": [
                "clean;",
                "make",
                "-j$(NPROCS)",
                "flash"
            ],
            "group": "build",
            "problemMatcher": []
        },
        {
            "label": "Clean",
            "command": "make",
            "args": [
                "clean"
            ],
            "group": "build",
            "problemMatcher": []
        },
        {
            "label": "Generate 'tasks.json'",
            "command": "make",
            "args": [
                "tasks"
            ],
            "group": "build",
            "problemMatcher": []
        },
        {
            "label": "Generate 'c_cpp_properties.json'",
            "command": "make",
            "args": [
                "c_cpp"
            ],
            "group": "build",
            "problemMatcher": []
        },
        {
            "label": "Generate 'launch.json'",
            "command": "make",
            "args": [
                "launch"
            ],
            "group": "build",
            "problemMatcher": []
        },
        {
            "label": "Pre-Launch",
            "command": "make",
            "args": [
                "launch",
                "clean;",
                "make",
                "-j$(NPROCS)",
                "debug"
            ],
            "group": "build",
            "problemMatcher": []
        }
    ]
}

endef

.PHONY: all

all: $(OUTFILE)

$(OUTFILE):
	$(file >$@,$(TASKS))
