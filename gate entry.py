# Importing necessary modules
import tkinter as tk
from tkinter import *
from tkinter import ttk
import mysql.connector as sqltor
import tkinter.messagebox
import time
import sys

ind=0
iid=0
sno=1

# Creating a class for the main window or the 'App'
class mainapp(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.geometry('1000x700+500+150')
        self.title('Gate Entry Record')
        self.resizable(False,False)
        self.bg=PhotoImage(file='background.png')
        b_label=Label(self,image=self.bg).place(x=0,y=0)
        self.frame=None
        self.switch_frame(Login,200)
    # A function to switch between different programs in the program
    def switch_frame(self,frame_class,place):
        new_frame=frame_class(self)
        if self.frame is not None:
            self.frame.destroy()
        self.frame=new_frame
        self.frame.place(x=place,y=150)
    # A function to establish connection with mysql
    def con_mysql(self,u,p):
        try:
            self.con=sqltor.connect(host='localhost',user=u,password=p)
            if self.con.is_connected():
                self.cur=self.con.cursor()
                # creating database and table if they do not exist
                self.cur.execute("create database if not exists school")
                self.cur.execute("use school")
                self.cur.execute("""create table if not exists gate_entry
                (First_Name char(50),Last_Name char(50),Contact_no char(10),PID_type char(20),
                PID_No char(20),Date_of_visit date,Time_of_Visit char(10),Reason char(200))""")
                tkinter.messagebox.showinfo('SUCCESS','Login Successful !')
                self.switch_frame(choose,200)

        except:
            # pop up window for displaying error message
            tkinter.messagebox.showerror('ERROR','Login Unsuccessful')
    # Function to enter records into the table of database
    def get_info(self,f,l,m,n,p,d,t,r):
        try:
            st="INSERT INTO gate_entry VALUES('{}','{}',{},'{}',{},'{}','{}','{}')".format(f,l,m,n,p,d,t,r)

            self.cur.execute(st)
            self.con.commit()
            # pop up window to show successful addition of record
            tkinter.messagebox.showinfo('SUCCESS','Record Added Successfully')
        except:
            # pop up window to show error message if addition failed
            tkinter.messagebox.showerror('ERROR','Kindly fill all field correctly')
    # Function to register a new user
    def New_user(self):
        # creating new pop up window for admin login
        self.admin=Toplevel()
        self.admin.geometry('400x200+750+400')
        a_l=Label(self.admin,text='Admin Login',width=20)
        a_l.place(x=130,y=30)
        a_frame=Frame(self.admin,bg='white',width=300,height=100)
        a_frame.place(x=50,y=50)
        au_l=Label(a_frame,text="Username:",width=10)
        au_l.grid(row=0,column=0)
        self.au_e=Entry(a_frame,width=30,bd=5)
        self.au_e.grid(row=0,column=1)
        ap_l=Label(a_frame,text="Password:",width=10)
        ap_l.grid(row=1,column=0)
        self.ap_e=Entry(a_frame,width=30,bd=5,show='*')
        self.ap_e.grid(row=1,column=1)
        ac_b=Button(a_frame,text='Cancel',width=10,bg='white',fg='black',command=self.admin.destroy).grid(sticky='w',row=2,column=0)
        al_b=Button(a_frame,text='Login',width=10,bg='white',fg='black',command=self.create_user_get).grid(sticky='w',row=2,column=1)
    # Function to get credentials of new user
    def create_user_get(self):
        au=self.au_e.get()
        ap=self.ap_e.get()
        try:
            # connect to mysql as root or admin
            self.a_con=sqltor.connect(host='localhost',user=au,password=ap)
            tkinter.messagebox.showinfo('SUCCESS','Login Successful')
            self.admin.destroy()
            create=Toplevel()
            create.geometry('400x200+750+400')
            c_l=Label(create,text='Create New User',width=20)
            c_l.place(x=130,y=30)
            c_frame=Frame(create,bg='white',width=300,height=100)
            c_frame.place(x=50,y=50)
            cu_l=Label(c_frame,text="Username:",width=10)
            cu_l.grid(row=0,column=0)
            self.cu_e=Entry(c_frame,width=30,bd=5)
            self.cu_e.grid(row=0,column=1)
            cp_l=Label(c_frame,text="Password:",width=10)
            cp_l.grid(row=1,column=0)
            self.cp_e=Entry(c_frame,width=30,bd=5,show='*')
            self.cp_e.grid(row=1,column=1)
            cc_b=Button(c_frame,text='Cancel',width=10,bg='white',fg='black',command=create.destroy)
            cc_b.grid(row=2,column=0)
            cl_b=Button(c_frame,text='Create',width=10,bg='white',fg='black',command=self.create_user)
            cl_b.grid(row=2,column=1,sticky='w')
        except:
            tkinter.messagebox.showerror('ERROR','Login Unsuccsessful')
    # Function to actually register the user in mysql database management system
    def create_user(self):
        try:
            cr_cur=self.a_con.cursor()
            cu=self.cu_e.get()
            cp=self.cp_e.get()
            bug="drop user '{}'@'localhost'".format(cu)
            bug1="flush privileges"
            stc="CREATE USER '{}'@'localhost' IDENTIFIED BY '{}';".format(cu,cp);
            print(stc)
            stg="grant all privileges on *.* to '{}'@'localhost'".format(cu)
            stf="flush privileges"
            cr_cur.execute(stc)
            cr_cur.execute(stg)
            cr_cur.execute(stf)
            tkinter.messagebox.showinfo('SUCCESS','User Added')
            cr_cur.close()
            self.a_con.close()
        except:
            tkinter.messagebox.showerror('ERROR','Cannot Add User\nUser already exists')

# Frame for The main login window
class Login(tk.Frame):
    def __init__(self,master):
        tk.Frame.__init__(self,master,bg='white',width=600,height=500)

        # making username and password appear on screen
        u_label=Label(self,text='Username',bg='white',fg='grey',font=("Calibri",15)).place(x=100,y=40)
        p_label=Label(self,text='Password',bg='white',fg='grey',font=('Calibri',15)).place(x=100,y=130)

        # Entry widget for getting input from user
        u=StringVar()
        p=StringVar()
        self.u_entry=Entry(self,width=70,bd=5,relief='sunken',textvariable=u)
        self.u_entry.place(x=100,y=70)
        self.p_entry=Entry(self,width=70,bd=5,relief='sunken',textvariable=p,show='*')
        self.p_entry.place(x=100,y=160)
        # Button for logging in
        sin_b=Button(self,text='Log In',command=lambda: master.con_mysql(u.get(),p.get()),width=10,bg='#0C9BE8',font=('Impact'),fg='white').place(x=435,y=200)
        q_b=Button(self,text='Quit',command=master.destroy,width=10,bg='#0C9BE8',font=('Impact'),fg='white').place(x=100,y=200)
        a_b=Button(self,text='New User',command=master.New_user,width=20,bg='#0C9BE8',font=('Impact'),fg='white').place(x=225,y=200)
# Frame for choosing action to be performed
class choose(tk.Frame):
    def __init__(self,master):
        tk.Frame.__init__(self,master,bg='white',width=600,height=500)
        c_l=Label(self,text="Choose Action",font=('Impact',20),fg='black',width=20,height=3,bd=0).place(x=180,y=20)
        add_b=Button(self,text="Add Record",width=20,height=10,bg='#0C9BE8',font=('Impact'),command=lambda: master.switch_frame(reg_page,200)).place(x=50,y=130)
        view_b=Button(self,text="View Records",width=20,height=10,bg='#0C9BE8',font=('Impact'),command=lambda: master.switch_frame(view_page,100)).place(x=330,y=130)

class view_page(tk.Frame):
    def __init__(self,master):
        self.curs=master.cur
        tk.Frame.__init__(self,master,bg='white',width=800,height=500)
        d_l=Label(self,text="Date of Visit",font=('Impact'),fg='black',height=1,bd=0).place(x=100,y=10)
        # Making the display window
        #d=StringVar()
        self.d_e=Entry(self,width=30,bd=5)
        s_b=Button(self,text='Search',bg='#0C9BE8',fg='white',command=self.display).place(x=430,y=9)
        r_b=Button(self,text='Reset',bg='#0C9BE8',fg='white',command=lambda: master.switch_frame(view_page,100)).place(x=380,y=300)
        b_b=Button(self,text='Back',bg='#0C9BE8',fg='white',command=lambda: master.switch_frame(choose,200)).place(x=420,y=300)
        self.d_e.place(x=230,y=10)
        # Creating a table to display stored records
        self.tree=ttk.Treeview(self)
        self.tree['columns']=(1,2,3,4,5,6)
        self.tree.column('#0',width=110,minwidth=80,stretch=tk.NO)
        self.tree.column(1,width=110,minwidth=80,stretch=tk.NO)
        self.tree.column(2,width=110,minwidth=80,stretch=tk.NO)
        self.tree.column(3,width=110,minwidth=80,stretch=tk.NO)
        self.tree.column(4,width=110,minwidth=80,stretch=tk.NO)
        self.tree.column(5,width=110,minwidth=80,stretch=tk.NO)
        self.tree.column(6,width=110,minwidth=80,stretch=tk.NO)
        self.tree.heading('#0',text="SNO",anchor=tk.W)
        self.tree.heading(1,text="First Name",anchor=tk.W)
        self.tree.heading(2,text="Last Name",anchor=tk.W)
        self.tree.heading(3,text="Contact No",anchor=tk.W)
        self.tree.heading(4,text="PID",anchor=tk.W)
        self.tree.heading(5,text="PID No",anchor=tk.W)
        self.tree.heading(6,text="DOV",anchor=tk.W)
        self.tree.place(x=10,y=40)
    def display(self):
        try:
            st="select * from gate_entry where Date_of_visit='{}'".format(self.d_e.get())
            self.curs.execute(st)
            rec=self.curs.fetchall()
            global ind
            global iid
            global sno
            for i in rec:
                self.tree.insert("", ind, iid,text=sno,values=i)
                ind=ind+1
                iid=iid+1
                sno=sno+1
        except:
            tk.messagebox.showerror('ERROR',"Enter valid date")

class reg_page(tk.Frame):
    def __init__(self,master):
        tk.Frame.__init__(self,master,bg='white',width=600,height=500)
        # First Name
        f_n=Label(self,text="First Name:",width=10,height=1,font=(15)).place(x=50,y=50)
        self.f_e=Entry(self,width=50,bd=5)
        self.f_e.place(x=200,y=50)

        #Last Name
        l_n=Label(self,text="Last Name:",width=10,height=1,font=(15)).place(x=50,y=90)
        self.l_e=Entry(self,width=50,bd=5)
        self.l_e.place(x=200,y=90)

        # Mobile number
        m_n=Label(self,text="Contact No:",width=10,height=1,font=(15)).place(x=50,y=130)
        self.m_e=Entry(self,width=50,bd=5)
        self.m_e.place(x=200,y=130)

        # Personal ID
        pid_n=Label(self,text="Personal ID:",width=10,height=1,font=(15)).place(x=50,y=170)
        self.pid_e=Entry(self,width=35,bd=5)
        self.pid_e.place(x=200,y=170)

        #Dropbox for type of Personal ID
        self.n=StringVar()
        self.p_type=ttk.Combobox(self,width=15,textvariable=self.n)
        self.p_type['values']=('Aadhaar Number',
                          'Liscence Number',
                          'PAN Number')
        self.p_type.place(x=450,y=170)
        self.p_type.current()

        # Date of Visit
        dov_n=Label(self,text="Date of Visit:",width=10,height=1,font=(15)).place(x=50,y=210)
        self.dov_e=Entry(self,width=50,bd=5)
        self.dov_e.place(x=200,y=210)

        # Time of visit
        time_n=Label(self,text="Time of visit:",width=10,height=1,font=(15)).place(x=50,y=250)
        self.time_e=Entry(self,width=40,bd=5)
        self.time_e.place(x=200,y=250)

        # Button for getting the current time of system
        time_b=Button(self,width=10,text='Current Time',height=1,command=self.cur_time).place(x=450,y=248)

        # Reason for visit
        res_n=Label(self,text="Reason for Visit:",width=12,height=1,font=(15)).place(x=50,y=290)
        self.res_e=Text(self,height=7,width=38,bd=5)
        self.res_e.place(x=200,y=290)

        # Button for next screen
        next_b=Button(self,text="Next",width=5,command=lambda : master.get_info(self.f_e.get(),
            self.l_e.get(),
            self.m_e.get(),
            self.n.get(),
            self.pid_e.get(),
            self.dov_e.get(),
            self.time_e.get(),
            self.res_e.get('1.0','end-1c')),bg='#0C9BE8',font=('Impact'),fg='white').place(x=400,y=450)

        # Button to quit the program
        quit_b=Button(self,text="Quit",width=5,command=master.destroy,bg='#0C9BE8',font=('Impact'),fg='white').place(x=350,y=450)
        # Button to add record
        r_b=Button(self,text='Reset',bg='#0C9BE8',fg='white',command=lambda: master.switch_frame(reg_page,200),width=5,font=('Impact')).place(x=290,y=450)
    # Function to get current time of the system
    def cur_time(self):
        if self.time_e.get()=="":
            x=time.strftime("%H:%M")
            self.time_e.insert(0,x)
        else:
            pass
# Making an object from class mainapp
obj=mainapp()
# Adding loop for main window
obj.mainloop()
