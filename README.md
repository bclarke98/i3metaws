# i3metaws

## So uh, what's it do?
This program aims to provide i3wm (or i3-gaps) users with a tool for expanding
the typical 1-10 workspace layout by adding 'meta-workspaces'. And for whatever
reason I kinda had an itch to write something in C. Probably because I've been
stuck with using C++ for the last 2 years of college...

A meta-workspace is simply a collection of standard workspaces. Until you
actually open up a new meta-workspace, the workspace behavior is identical
to using the regular workspaces 1-10, since i3metaws will just put them into
meta-workspace 0. When you open a workspace, it's stored into the current
meta-workspace. When you swap to a new meta-workspace, you'll see the same
empty workspaces you had when you launched `startx`. If you want to go back
to your original workspaces, you just swap back to the meta-workspace they're
stored in.

**TL;DR, this program lets you avoid having to reshuffle which windows are on
which workspaces when starting a new project (or just want to compartmentalize
your workflow even more).**

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
functionality. The final step is just to change the default initial workspace
name from "1", "2", etc. to "01", "02", ...

In your i3 config, replace all your `bindsym $mod+[N] workspace [N]` with
`bindsym $mod+[N] exec i3metaws -w [N]`, where [N] is just the workspace number.

Next, replace your `bindsym $mod+Shift+[N] move container to workspace [N]`
with `bindsym $mod+Shift+[N] exec i3metaws -m [N]`.

Now add `bindsym $mod+Control+[N] exec i3metaws -M [N]` for each
workspace N.

Finally, we have to tell i3 to open on workspace '01' when we run `startx`
instead of opening to just workspace '1' since i3metaws expects at least 2
characters (one for the meta-workspace we're on and the other for the actual
workspace). **Note: if you only have a single display, you won't need the
i3-msg part of the following code block.**
If you have multiple displays, i3 will open your default workspace on your
primary display and subsequent workspaces on the rest of your displays, so
we need to make sure that they're updated to use '0N' instead of 'N' as well.
The order doesn't really matter, but keep in mind that the last workspace you
specify will be the focused workspace when the X-server launches.
So, for each display, add

```
exec --no-startup-id "i3-msg workspace [N] && i3metaws -w [N]"
```

for each [N] display you're using. For whatever reason it needs to all be in a
single `exec` command, so just && them all together. If you want an example of
how it should look, check the excerpt from my config file below. If anyone
figures out why this seems to be the case, feel free to let me know.

Also, if you have more than two displays, you'll probably have to manually tell
i3 which display matches up with which workspace. You can find the display
information by running `xrandr` in your terminal. If you need help, you can
check the i3 docs online, they're awesome. And as always, `man i3` is your
friend.

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

exec --no-startup-id "i3-msg 'workspace 2' && i3metaws -w $ws2 && i3-msg 'workspace 1' && i3metaws -w $ws1"

```
