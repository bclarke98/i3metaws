# i3metaws
This program aims to provide i3wm (or i3-gaps) users with an extremely
lightweight tool for expanding the typical 1-10 workspace layout by adding
'meta-workspaces'.

A meta-workspace is simply a collection of standard workspaces. Until you
actually open up a new meta-workspace, the workspace behavior is identical
to using the regular workspaces 1-10, since i3metaws will just put them into
meta-workspace 0. When you open a workspace, it's stored into the current
meta-workspace. When you swap to a new meta-workspace, you'll see the same
empty workspaces you had when you launched `startx`. If you want to go back
to your original workspaces, you just swap back to the meta-workspace they're
stored in.

TL;DR, this program lets you avoid having to reshuffle which windows are on
which workspaces when starting a new project (or just want to compartmentalize
your workflow even more).

## Installation
The following commands will install i3metaws to /usr/local/bin.

If you want to change the install location, modify `INSTALL_DIR` in
the Makefile before running `make install`.
```
git clone https://github.com/bclarke98/i3metaws.git
cd i3metaws
sudo make install
```

## Usage
The following two steps don't actually change any functionality of your
workspaces, but they're needed so that i3metaws can keep track of which
workspaces are open. The third step is what actually adds the meta-workspace
functionality. The final step is just to change the default initial workspace(s)
names from "1", "2", etc. to "01", "02", ...

1. In your i3 config, replace all your `bindsym $mod+[N] workspace [N]` with
`bindsym $mod+[N] exec i3metaws -w [N]`, where [N] is just the workspace number.

2. Next, replace your `bindsym $mod+Shift+[N] move container to workspace [N]`
with `bindsym $mod+Shift+[N] exec i3metaws -m [N]`.

3. Now add `bindsym $mod+Control+[N] exec i3metaws -M [N]` for each
workspace N.

4. Finally, we have to tell i3 to open on workspace '01' when we run `startx`
instead of opening to just workspace '1' since i3metaws expects at least 2
characters (one for the meta-workspace we're on and the other for the actual
workspace).

If you have multiple displays, i3 will open your default workspace on your
primary display and subsequent workspaces on the rest of your displays, so
we need to make sure that they're updated to use '0N' instead of 'N' as well.
The order doesn't really matter as long as the last `exec` you add in this step
is for the workspace on your primary display (or whichever display you want to
be focused when the X server loads).

So, for each display, add `exec --no-startup-id i3metaws -w [N]` for each [N]
display you're using.

## Full Bindsym Example
This is how I have things set up in my i3 config (using two monitors)
```
set $ws1 "1"
set $ws2 "2"
set $ws3 "3"
set $ws4 "4"
set $ws5 "5"
set $ws6 "6"
set $ws7 "7"
set $ws8 "8"
set $ws9 "9"
set $ws10 "0"

bindsym $mod+1 exec --no-startup-id i3metaws -w $ws1
bindsym $mod+2 exec --no-startup-id i3metaws -w $ws2
bindsym $mod+3 exec --no-startup-id i3metaws -w $ws3
bindsym $mod+4 exec --no-startup-id i3metaws -w $ws4
bindsym $mod+5 exec --no-startup-id i3metaws -w $ws5
bindsym $mod+6 exec --no-startup-id i3metaws -w $ws6
bindsym $mod+7 exec --no-startup-id i3metaws -w $ws7
bindsym $mod+8 exec --no-startup-id i3metaws -w $ws8
bindsym $mod+9 exec --no-startup-id i3metaws -w $ws9
bindsym $mod+0 exec --no-startup-id i3metaws -w $ws10

bindsym $mod+Shift+1 exec --no-startup-id i3metaws -m $ws1
bindsym $mod+Shift+2 exec --no-startup-id i3metaws -m $ws2
bindsym $mod+Shift+3 exec --no-startup-id i3metaws -m $ws3
bindsym $mod+Shift+4 exec --no-startup-id i3metaws -m $ws4
bindsym $mod+Shift+5 exec --no-startup-id i3metaws -m $ws5
bindsym $mod+Shift+6 exec --no-startup-id i3metaws -m $ws6
bindsym $mod+Shift+7 exec --no-startup-id i3metaws -m $ws7
bindsym $mod+Shift+8 exec --no-startup-id i3metaws -m $ws8
bindsym $mod+Shift+9 exec --no-startup-id i3metaws -m $ws9
bindsym $mod+Shift+0 exec --no-startup-id i3metaws -m $ws10

bindsym $mod+Control+1 exec --no-startup-id i3metaws -M $ws1
bindsym $mod+Control+2 exec --no-startup-id i3metaws -M $ws2
bindsym $mod+Control+3 exec --no-startup-id i3metaws -M $ws3
bindsym $mod+Control+4 exec --no-startup-id i3metaws -M $ws4
bindsym $mod+Control+5 exec --no-startup-id i3metaws -M $ws5
bindsym $mod+Control+6 exec --no-startup-id i3metaws -M $ws6
bindsym $mod+Control+7 exec --no-startup-id i3metaws -M $ws7
bindsym $mod+Control+8 exec --no-startup-id i3metaws -M $ws8
bindsym $mod+Control+9 exec --no-startup-id i3metaws -M $ws9
bindsym $mod+Control+0 exec --no-startup-id i3metaws -M $ws10

exec --no-startup-id i3metaws -w $ws2
exec --no-startup-id i3metaws -w $ws1
```
