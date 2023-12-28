#run the homing, will parse out the axis vari from button command, searches ini file for other info.
def goto_home(axis):
    if s.interp_state == linuxcnc.INTERP_IDLE:
        home = inifile.find('JOINT_' + str(inifile.find('TRAJ', 'COORDINATES').upper().index(axis)), 'HOME')
        mode = s.task_mode
        if s.task_mode != linuxcnc.MODE_MDI:
            c.mode(linuxcnc.MODE_MDI)
        c.mdi('G53 G0 ' + axis + home)


#run the touch off by sending /setting via mdi
def run_touch_off():
    #swag - run this when not running a program??
    if s.interp_state == linuxcnc.INTERP_IDLE:
        mode = s.task_mode
        #swag - make sure we aren't in MDI mode, to conflict, or weird behavior??
        if s.task_mode != linuxcnc.MODE_MDI:
            c.mode(linuxcnc.MODE_MDI)
        
        #send MDI command on button press
        #macro updated for 0.760
        c.mdi('G4 P3')            #snooze 3, are you ready?
        c.mdi('G10 L20 P0 Z0')    #set current z to z zero
        c.mdi('G91')              #probe for initial contact
        c.mdi('F10')                
        c.mdi('G38.2 Z-0.50')
        c.mdi('F10')                
        c.mdi('G1 Z0.1')                
        c.mdi('G1 P0.5')          #snooze 0.25
        c.mdi('G38.2 Z-0.20')     #move off then probe slow
        c.mdi('G1 Z0.5 F10')      #move up to set new zero
        c.mdi('G10 L20 P0 Z1.26') #set Z0 at trigger point plus plate offset


#------------------------------------------------------------------------------------------------------------------------
# make the buttons
root_window.tk.call('button','.pane.top.tabs.fmanual.home_y','-text','Custom - Home Y ','-command','goto_home Y','-height','1')
root_window.tk.call('button','.pane.top.tabs.fmanual.g2','-text','Custom - Touch Off','-command','run_touch_off','-height','1')


# place the buttons
root_window.tk.call('grid','.pane.top.tabs.fmanual.home_y','-column','0','-row','7','-columnspan','1','-padx','3','-sticky','w')
root_window.tk.call('grid','.pane.top.tabs.fmanual.g2','-column','0','-row','8','-columnspan','2','-padx','3','-sticky','w')


#------------------------------------------------------------------------------------------------------------------------
# any function called from tcl needs to be added to TclCommands
TclCommands.goto_home = goto_home
TclCommands.run_touch_off = run_touch_off
commands = TclCommands(root_window)
