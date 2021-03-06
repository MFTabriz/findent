  std::cout << "# -*- coding: utf-8 -*-" << std::endl;
  std::cout << "#  Findent plugin" << std::endl;
  std::cout << "#  This file is part of gedit" << std::endl;
  std::cout << "#" << std::endl;
  std::cout << "#  Copyright (C) 2017 Willem Vermin" << std::endl;
  std::cout << "#" << std::endl;
  std::cout << "#  This program is free software; you can redistribute it and/or modify" << std::endl;
  std::cout << "#  it under the terms of the GNU General Public License as published by" << std::endl;
  std::cout << "#  the Free Software Foundation; either version 2 of the License, or" << std::endl;
  std::cout << "#  (at your option) any later version." << std::endl;
  std::cout << "#" << std::endl;
  std::cout << "#  This program is distributed in the hope that it will be useful," << std::endl;
  std::cout << "#  but WITHOUT ANY WARRANTY; without even the implied warranty of" << std::endl;
  std::cout << "#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << std::endl;
  std::cout << "#  GNU General Public License for more details." << std::endl;
  std::cout << "#" << std::endl;
  std::cout << "#  You should have received a copy of the GNU General Public License" << std::endl;
  std::cout << "#  along with this program; if not, write to the Free Software" << std::endl;
  std::cout << "#  Foundation, Inc., 51 Franklin Street, Fifth Floor," << std::endl;
  std::cout << "#  Boston, MA 02110-1301, USA." << std::endl;
  std::cout << "" << std::endl;
  std::cout << "from gi.repository import GObject, Gio, Gtk, Gedit" << std::endl;
  std::cout << "import gettext" << std::endl;
  std::cout << "import os.path" << std::endl;
  std::cout << "from subprocess import Popen,PIPE" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "try:" << std::endl;
  std::cout << "    gettext.bindtextdomain(GETTEXT_PACKAGE, GP_LOCALEDIR)" << std::endl;
  std::cout << "    _ = lambda s: gettext.dgettext(GETTEXT_PACKAGE, s)" << std::endl;
  std::cout << "except:" << std::endl;
  std::cout << "    _ = lambda s: s" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "class FindentAppActivatable(GObject.Object, Gedit.AppActivatable):" << std::endl;
  std::cout << "    app = GObject.Property(type=Gedit.App)" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def __init__(self):" << std::endl;
  std::cout << "        GObject.Object.__init__(self)" << std::endl;
  std::cout << "        global shortcut" << std::endl;
  std::cout << "        shortcut = \"<Ctrl><Alt>f\"" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def do_activate(self):" << std::endl;
  std::cout << "        self.app.add_accelerator(shortcut, \"win.findent\", None)" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def do_deactivate(self):" << std::endl;
  std::cout << "        self.app.remove_accelerator(\"win.findent\", None)" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "class FindentWindowActivatable(GObject.Object, Gedit.WindowActivatable):" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    window = GObject.Property(type=Gedit.Window)" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def __init__(self):" << std::endl;
  std::cout << "        GObject.Object.__init__(self)" << std::endl;
  std::cout << "        self.bottom_bar = Gtk.Box()" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def do_activate(self):" << std::endl;
  std::cout << "        action = Gio.SimpleAction(name=\"findent\")" << std::endl;
  std::cout << "        action.connect('activate', lambda a, p: self.do_findent())" << std::endl;
  std::cout << "        self.window.add_action(action)" << std::endl;
  std::cout << "        self._insert_bottom_panel()" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def do_deactivate(self):" << std::endl;
  std::cout << "        self.window.remove_action(\"findent\")" << std::endl;
  std::cout << "        self._remove_bottom_panel()" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def do_update_state(self):" << std::endl;
  std::cout << "        view = self.window.get_active_view()" << std::endl;
  std::cout << "        enable = view is not None and view.get_editable()" << std::endl;
  std::cout << "        self.window.lookup_action(\"findent\").set_enabled(enable)" << std::endl;
  std::cout << "        return" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def do_findent(self):" << std::endl;
  std::cout << "        view = self.window.get_active_view()" << std::endl;
  std::cout << "        if view and hasattr(view, \"findent_view_activatable\"):" << std::endl;
  std::cout << "            view.findent_view_activatable.do_findent()" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def _insert_bottom_panel(self):" << std::endl;
  std::cout << "        # Add elements to panel." << std::endl;
  std::cout << "        self.findent_label = Gtk.Label()" << std::endl;
  std::cout << "        self.findent_textbuffer = Gtk.TextBuffer()" << std::endl;
  std::cout << "        global mesg" << std::endl;
  std::cout << "        mesg = self.findent_textbuffer" << std::endl;
  std::cout << "        self.findent_textview = Gtk.TextView()" << std::endl;
  std::cout << "        self.findent_textview.set_buffer(self.findent_textbuffer)" << std::endl;
  std::cout << "        self.bottom_bar.add(self.findent_textview)" << std::endl;
  std::cout << "        # Get bottom bar (A Gtk.Stack) and add our bar.        " << std::endl;
  std::cout << "        panel = self.window.get_bottom_panel()" << std::endl;
  std::cout << "        panel.add_titled(self.bottom_bar, 'findent_panel', \"Findent output\")" << std::endl;
  std::cout << "        # Make sure everything shows up." << std::endl;
  std::cout << "        panel.show()" << std::endl;
  std::cout << "        self.bottom_bar.show_all()" << std::endl;
  std::cout << "        panel.set_visible_child(self.bottom_bar)" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def _remove_bottom_panel(self):" << std::endl;
  std::cout << "        panel = self.window.get_bottom_panel()" << std::endl;
  std::cout << "        panel.remove(self.bottom_bar)" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def settext(self,text):" << std::endl;
  std::cout << "        self.findent_textbuffer.set_text(text)" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "class FindentViewActivatable(GObject.Object, Gedit.ViewActivatable):" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    view = GObject.Property(type=Gedit.View)" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def __init__(self):" << std::endl;
  std::cout << "        GObject.Object.__init__(self)" << std::endl;
  std::cout << "        self.default_flags = \"-Ia -i3\"" << std::endl;
  std::cout << "        self.executable = \"findent\"" << std::endl;
  std::cout << "        self.userflags = os.getenv(\"GEDIT_FINDENT_FLAGS\")" << std::endl;
  std::cout << "        if self.userflags == None:" << std::endl;
  std::cout << "            self.userflags = \"\"" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def do_activate(self):" << std::endl;
  std::cout << "        self.view.findent_view_activatable = self" << std::endl;
  std::cout << "        self.view.connect('populate-popup', self.populate_popup)" << std::endl;
  std::cout << "        mesg.set_text(\"Findent ready for use.\"+ \\" << std::endl;
  std::cout << "            \" Shortcut: \"+shortcut+ \\" << std::endl;
  std::cout << "            \" and in popup menu.\" + \\" << std::endl;
  std::cout << "            \" Default flags: '\" + self.default_flags + \"'\" + \\" << std::endl;
  std::cout << "            \"\\nflags from environment variable GEDIT_FINDENT_FLAGS: '\" + " << std::endl;
  std::cout << "            self.userflags+\"'\")" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def do_deactivate(self):" << std::endl;
  std::cout << "        delattr(self.view, \"findent_view_activatable\")" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def populate_popup(self, view, popup):" << std::endl;
  std::cout << "        if not isinstance(popup, Gtk.MenuShell):" << std::endl;
  std::cout << "            return" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        item = Gtk.SeparatorMenuItem()" << std::endl;
  std::cout << "        item.show()" << std::endl;
  std::cout << "        popup.append(item)" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        item = Gtk.MenuItem.new_with_mnemonic(_('_Findent'))" << std::endl;
  std::cout << "        item.set_sensitive(self.view.get_editable())" << std::endl;
  std::cout << "        item.show()" << std::endl;
  std::cout << "        item.connect('activate', lambda i: self.do_findent())" << std::endl;
  std::cout << "        popup.append(item)" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    def do_findent(self):" << std::endl;
  std::cout << "        doc = self.view.get_buffer()" << std::endl;
  std::cout << "        if doc is None:" << std::endl;
  std::cout << "            return" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        ctype = doc.get_content_type()" << std::endl;
  std::cout << "        if ctype != \"text/x-fortran\":" << std::endl;
  std::cout << "            mesg.set_text(\"Content type is '\"+ctype+\"'\" + \\" << std::endl;
  std::cout << "                    \". Findent handles only 'text/x-fortran'\")" << std::endl;
  std::cout << "            return" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        # run a simple test to see if findent is doing what we expect" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        srcin = \"program test\\ncontinue\\nend program test\"" << std::endl;
  std::cout << "        expected = \"program test\\n   continue\\nend program test\\n\"" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        try:" << std::endl;
  std::cout << "            with Popen([self.executable,\"-i3\"], stdout=PIPE, stdin=PIPE) as proc:" << std::endl;
  std::cout << "                srcout = proc.communicate(str.encode(srcin))[0].decode()" << std::endl;
  std::cout << "        except OSError:" << std::endl;
  std::cout << "            mesg.set_text(\"Cannot find findent.\" + \\" << std::endl;
  std::cout << "                    \"\\nTake care that the location of findent is in PATH\" +\\" << std::endl;
  std::cout << "                    \"\\nUsing '\"+self.executable+\"'\")" << std::endl;
  std::cout << "            return" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        if srcout != expected:" << std::endl;
  std::cout << "            mesg.set_text(\"Findent is not functioning as expected.\" +\\" << std::endl;
  std::cout << "                    \"\\nTake care that the location of findent is in PATH\" +\\" << std::endl;
  std::cout << "                    \"\\nUsing '\"+self.executable+\"'\")" << std::endl;
  std::cout << "            return" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        xy = self.view.window_to_buffer_coords(Gtk.TextWindowType.TEXT,0,0)" << std::endl;
  std::cout << "        z = self.view.get_line_at_y(xy[1])[0]" << std::endl;
  std::cout << "        line = z.get_line()" << std::endl;
  std::cout << "        cline = doc.get_iter_at_mark(doc.get_insert()).get_line()" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        srcin = doc.get_text(doc.get_start_iter(),doc.get_end_iter(),True)" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        uri = doc.get_location().get_uri()" << std::endl;
  std::cout << "        suffix = os.path.splitext(uri)[1].lower()" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        if suffix in {\".f\",\".for\",\".fpp\",\".ftn\",\".fortran\",\".f77\"}:" << std::endl;
  std::cout << "            ff = \"-ifixed\"" << std::endl;
  std::cout << "        elif suffix in {\".f90\",\".f95\",\".f03\",\".f08\"}:" << std::endl;
  std::cout << "            ff = \"-ifree\"" << std::endl;
  std::cout << "        else:" << std::endl;
  std::cout << "            ff = \"-iauto\"" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        flags = self.default_flags.split() + [ff] + self.userflags.split()" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        try:" << std::endl;
  std::cout << "            with Popen([self.executable]+flags, stdout=PIPE, stdin=PIPE) as proc:" << std::endl;
  std::cout << "                srcout = proc.communicate(str.encode(srcin))[0].decode()" << std::endl;
  std::cout << "        except OSError:" << std::endl;
  std::cout << "            mesg.set_text(\"Cannot find findent.\" + \\" << std::endl;
  std::cout << "                    \"\\nTake care that the location of findent is in PATH\" +\\" << std::endl;
  std::cout << "                    \"\\nUsing '\"+self.executable+\"'\")" << std::endl;
  std::cout << "            return" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        orig_lines = doc.get_line_count()" << std::endl;
  std::cout << "        doc.set_text(srcout)" << std::endl;
  std::cout << "        while Gtk.events_pending():" << std::endl;
  std::cout << "            Gtk.main_iteration_do(False)" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        hop = doc.get_iter_at_line(line)" << std::endl;
  std::cout << "        self.view.scroll_to_iter(hop,0,True,0,0)" << std::endl;
  std::cout << "        doc.goto_line(cline)" << std::endl;
  std::cout << "        lines = doc.get_line_count()" << std::endl;
  std::cout << "        s = \"\"" << std::endl;
  std::cout << "        for i in flags:" << std::endl;
  std::cout << "            s = s+\" \"+i" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        mesg.set_text(\"flags used: \"+s+\" \\n\"+ \\" << std::endl;
  std::cout << "                str(lines)+\" lines indented\")" << std::endl;
  std::cout << "        if lines == orig_lines+1:" << std::endl;
  std::cout << "            mesg.insert_at_cursor(\", empty line added\")" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "        if lines != orig_lines and lines != orig_lines+1:" << std::endl;
  std::cout << "            mesg.insert_at_cursor(\"\\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\")" << std::endl;
  std::cout << "            mesg.insert_at_cursor(\"\\nXX MALFUNCTION DETECTED, UNDO TWICE! XX\")" << std::endl;
  std::cout << "            mesg.insert_at_cursor(\"\\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\")" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "# ex:ts=4:et:" << std::endl;
