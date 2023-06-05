tell application "System Events"
    tell process "qemu-system-i386"
        set frontmost to true
        set position of front window to {1966, 143}
    end tell
end tell
