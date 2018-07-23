Public Class Form1
    Inherits System.Windows.Forms.Form

    Public serHandle1 As Integer    ' motor 1
    Public serHandle2 As Integer    ' motor 2
    Public serHandle3 As Integer    ' brightlight 1
    Public serHandle4 As Integer    ' brightlight 2

    Public motorType1 As Integer
    Public motorType2 As Integer

    Public temp As Integer


#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

        ' connect to the motor controller on COM1
        serHandle1 = SerConnectionConnect(1, DEF_MOTOR_CONTROLLER)         ' connect to port 1, Motor controller

        While serHandle1 = &H0
            Dim response As MsgBoxResult
            response = MsgBox("COM PORT 1 did not open or connect", MsgBoxStyle.AbortRetryIgnore)
            If response = MsgBoxResult.Retry Then   ' User chose Yes.
                serHandle1 = SerConnectionConnect(1, DEF_MOTOR_CONTROLLER)         ' connect to port 1, Motor controller
            ElseIf response = MsgBoxResult.Ignore Then
                Exit While
            Else
                Throw New System.Exception("Program Canceled")
            End If

        End While

        SerConnectionRead(serHandle1, REG_SYS_PRODUCTID_SUBCLASS, motorType1)            ' find out what kind of controller

        Select Case motorType1
            Case 1
                Motor1.Text = "MicroMo Stepper"
            Case 2
                Motor1.Text = "Vexta 5-Phase "
            Case 3
                Motor1.Text = "2-Axis DC"
            Case Else
                Motor1.Text = "MicroMo Stepper"
        End Select

        If serHandle1 = &H0 Then
            Motor1.Text = "No Controller"
        End If

        SerConnectionRead(serHandle1, REG_USER_STATUS_1, temp)            ' read motor state
        State_1_1.Text = temp

        SerConnectionRead(serHandle1, REG_USER_CURRENT_1, temp)            ' read motor location
        Location_1_1.Text() = temp

        SerConnectionRead(serHandle1, REG_USER_STATUS_2, temp)            ' read motor state
        State_2_1.Text = temp

        SerConnectionRead(serHandle1, REG_USER_CURRENT_2, temp)            ' read motor location
        Location_2_1.Text() = temp


        ' connect to the motor controller on COM2
        serHandle2 = SerConnectionConnect(2, DEF_MOTOR_CONTROLLER)         ' connect to port 2, Motor controller

        While serHandle2 = &H0
            Dim response As MsgBoxResult
            response = MsgBox("COM PORT 2 did not open or connect", MsgBoxStyle.AbortRetryIgnore)
            If response = MsgBoxResult.Retry Then   ' User chose Yes.
                serHandle1 = SerConnectionConnect(2, DEF_MOTOR_CONTROLLER)         ' connect to port 2, Motor controller
            ElseIf response = MsgBoxResult.Ignore Then
                Exit While
            Else
                Throw New System.Exception("Program Canceled")
            End If

        End While

        SerConnectionRead(serHandle2, REG_SYS_PRODUCTID_SUBCLASS, motorType1)            ' find out what kind of controller

        Select Case motorType2
            Case 1
                Motor2.Text = "MicroMo Stepper"
            Case 2
                Motor2.Text = "Vexta 5-Phase "
            Case 3
                Motor2.Text = "2-Axis DC"
            Case Else
                Motor2.Text = "MicroMo Stepper"
        End Select

        If serHandle2 = &H0 Then
            Motor2.Text = "No Controller"
        End If


        SerConnectionRead(serHandle2, REG_USER_STATUS_1, temp)            ' read motor state
        State_1_2.Text = temp

        SerConnectionRead(serHandle2, REG_USER_CURRENT_1, temp)            ' read motor location
        Location_1_2.Text() = temp

        SerConnectionRead(serHandle2, REG_USER_STATUS_2, temp)            ' read motor state
        State_2_2.Text = temp

        SerConnectionRead(serHandle2, REG_USER_CURRENT_2, temp)            ' read motor location
        Location_2_2.Text() = temp




        ' connect to the brightlight on COM3
        serHandle3 = SerConnectionConnect(3, DEF_BRIGHTLIGHT)         ' connect to port 3, brightlight 1

        While serHandle3 = &H0
            Dim response As MsgBoxResult
            response = MsgBox("COM PORT 3 did not open or connect", MsgBoxStyle.AbortRetryIgnore)
            If response = MsgBoxResult.Retry Then   ' User chose Yes.
                serHandle1 = SerConnectionConnect(3, DEF_BRIGHTLIGHT)   ' connect to port 3, brightlight 1
            ElseIf response = MsgBoxResult.Ignore Then
                Exit While
            Else
                Throw New System.Exception("Program Canceled")
            End If

        End While

        If serHandle3 = &H0 Then
            BrightLight1.Text = "No BrightLight"
        End If

        SerConnectionRead(serHandle3, REG_PWM_ABSOLUTE, temp)            ' read brightlight 1
        Value1.Text() = temp / 10



        ' connect to the brightlight on COM4
        serHandle4 = SerConnectionConnect(4, DEF_BRIGHTLIGHT)         ' connect to port 4, brightlight 2

        While serHandle4 = &H0
            Dim response As MsgBoxResult
            response = MsgBox("COM PORT 4 did not open or connect", MsgBoxStyle.AbortRetryIgnore)
            If response = MsgBoxResult.Retry Then   ' User chose Yes.
                serHandle1 = SerConnectionConnect(4, DEF_BRIGHTLIGHT)   ' connect to port 4, brightlight 2
            ElseIf response = MsgBoxResult.Ignore Then
                Exit While
            Else
                Throw New System.Exception("Program Canceled")
            End If


        End While
        If serHandle4 = &H0 Then
            BrightLight2.Text = "No BrightLight"
        End If

        SerConnectionRead(serHandle4, REG_PWM_ABSOLUTE, temp)            ' read brightlight 2
        Value2.Text() = temp / 10



        Timer1.Interval = 250
        Timer1.Enabled = True


    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents Button_2_Limit2 As System.Windows.Forms.Button
    Friend WithEvents Button_2_Plus2 As System.Windows.Forms.Button
    Friend WithEvents Button_2_GOTO2 As System.Windows.Forms.Button
    Friend WithEvents Button_2_Minus2 As System.Windows.Forms.Button
    Friend WithEvents Button_2_Home2 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Limit2 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Plus2 As System.Windows.Forms.Button
    Friend WithEvents Button_1_GOTO2 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Minus2 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Home2 As System.Windows.Forms.Button
    Friend WithEvents State_2_2 As System.Windows.Forms.TextBox
    Friend WithEvents Location_2_2 As System.Windows.Forms.TextBox
    Friend WithEvents State_1_2 As System.Windows.Forms.TextBox
    Friend WithEvents Location_1_2 As System.Windows.Forms.TextBox
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents Button_2_Limit1 As System.Windows.Forms.Button
    Friend WithEvents Button_2_Plus1 As System.Windows.Forms.Button
    Friend WithEvents Button_2_GOTO1 As System.Windows.Forms.Button
    Friend WithEvents Button_2_Minus1 As System.Windows.Forms.Button
    Friend WithEvents Button_2_Home1 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Limit1 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Plus1 As System.Windows.Forms.Button
    Friend WithEvents Button_1_GOTO1 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Minus1 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Home1 As System.Windows.Forms.Button
    Friend WithEvents State_2_1 As System.Windows.Forms.TextBox
    Friend WithEvents Location_2_1 As System.Windows.Forms.TextBox
    Friend WithEvents State_1_1 As System.Windows.Forms.TextBox
    Friend WithEvents Location_1_1 As System.Windows.Forms.TextBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Button_FullOn1 As System.Windows.Forms.Button
    Friend WithEvents Button_Plus1 As System.Windows.Forms.Button
    Friend WithEvents Button_Mid1 As System.Windows.Forms.Button
    Friend WithEvents Button_Minus1 As System.Windows.Forms.Button
    Friend WithEvents Button_Off1 As System.Windows.Forms.Button
    Friend WithEvents Value1 As System.Windows.Forms.TextBox
    Friend WithEvents Button_FullOn2 As System.Windows.Forms.Button
    Friend WithEvents Button_Plus2 As System.Windows.Forms.Button
    Friend WithEvents Button_Mid2 As System.Windows.Forms.Button
    Friend WithEvents Button_Minus2 As System.Windows.Forms.Button
    Friend WithEvents Button_Off2 As System.Windows.Forms.Button
    Friend WithEvents Value2 As System.Windows.Forms.TextBox
    Friend WithEvents BrightLight1 As System.Windows.Forms.GroupBox
    Friend WithEvents BrightLight2 As System.Windows.Forms.GroupBox
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents Motor1 As System.Windows.Forms.GroupBox
    Friend WithEvents Motor2 As System.Windows.Forms.GroupBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Me.Button_2_Limit2 = New System.Windows.Forms.Button
        Me.Button_2_Plus2 = New System.Windows.Forms.Button
        Me.Button_2_GOTO2 = New System.Windows.Forms.Button
        Me.Button_2_Minus2 = New System.Windows.Forms.Button
        Me.Button_2_Home2 = New System.Windows.Forms.Button
        Me.Button_1_Limit2 = New System.Windows.Forms.Button
        Me.Button_1_Plus2 = New System.Windows.Forms.Button
        Me.Button_1_GOTO2 = New System.Windows.Forms.Button
        Me.Button_1_Minus2 = New System.Windows.Forms.Button
        Me.Button_1_Home2 = New System.Windows.Forms.Button
        Me.State_2_2 = New System.Windows.Forms.TextBox
        Me.Location_2_2 = New System.Windows.Forms.TextBox
        Me.State_1_2 = New System.Windows.Forms.TextBox
        Me.Location_1_2 = New System.Windows.Forms.TextBox
        Me.Label5 = New System.Windows.Forms.Label
        Me.Label6 = New System.Windows.Forms.Label
        Me.Button_2_Limit1 = New System.Windows.Forms.Button
        Me.Button_2_Plus1 = New System.Windows.Forms.Button
        Me.Button_2_GOTO1 = New System.Windows.Forms.Button
        Me.Button_2_Minus1 = New System.Windows.Forms.Button
        Me.Button_2_Home1 = New System.Windows.Forms.Button
        Me.Button_1_Limit1 = New System.Windows.Forms.Button
        Me.Button_1_Plus1 = New System.Windows.Forms.Button
        Me.Button_1_GOTO1 = New System.Windows.Forms.Button
        Me.Button_1_Minus1 = New System.Windows.Forms.Button
        Me.Button_1_Home1 = New System.Windows.Forms.Button
        Me.State_2_1 = New System.Windows.Forms.TextBox
        Me.Location_2_1 = New System.Windows.Forms.TextBox
        Me.State_1_1 = New System.Windows.Forms.TextBox
        Me.Location_1_1 = New System.Windows.Forms.TextBox
        Me.Label4 = New System.Windows.Forms.Label
        Me.Label3 = New System.Windows.Forms.Label
        Me.Label2 = New System.Windows.Forms.Label
        Me.Label1 = New System.Windows.Forms.Label
        Me.BrightLight1 = New System.Windows.Forms.GroupBox
        Me.Button_FullOn1 = New System.Windows.Forms.Button
        Me.Button_Plus1 = New System.Windows.Forms.Button
        Me.Button_Mid1 = New System.Windows.Forms.Button
        Me.Button_Minus1 = New System.Windows.Forms.Button
        Me.Button_Off1 = New System.Windows.Forms.Button
        Me.Value1 = New System.Windows.Forms.TextBox
        Me.BrightLight2 = New System.Windows.Forms.GroupBox
        Me.Button_FullOn2 = New System.Windows.Forms.Button
        Me.Button_Plus2 = New System.Windows.Forms.Button
        Me.Button_Mid2 = New System.Windows.Forms.Button
        Me.Button_Minus2 = New System.Windows.Forms.Button
        Me.Button_Off2 = New System.Windows.Forms.Button
        Me.Value2 = New System.Windows.Forms.TextBox
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.Motor1 = New System.Windows.Forms.GroupBox
        Me.Motor2 = New System.Windows.Forms.GroupBox
        Me.BrightLight1.SuspendLayout()
        Me.BrightLight2.SuspendLayout()
        Me.SuspendLayout()
        '
        'Button_2_Limit2
        '
        Me.Button_2_Limit2.Location = New System.Drawing.Point(464, 288)
        Me.Button_2_Limit2.Name = "Button_2_Limit2"
        Me.Button_2_Limit2.TabIndex = 108
        Me.Button_2_Limit2.Text = "Limit"
        '
        'Button_2_Plus2
        '
        Me.Button_2_Plus2.Location = New System.Drawing.Point(464, 256)
        Me.Button_2_Plus2.Name = "Button_2_Plus2"
        Me.Button_2_Plus2.TabIndex = 107
        Me.Button_2_Plus2.Text = "+ 100"
        '
        'Button_2_GOTO2
        '
        Me.Button_2_GOTO2.Location = New System.Drawing.Point(464, 224)
        Me.Button_2_GOTO2.Name = "Button_2_GOTO2"
        Me.Button_2_GOTO2.TabIndex = 106
        Me.Button_2_GOTO2.Text = "GOTO 1000"
        '
        'Button_2_Minus2
        '
        Me.Button_2_Minus2.Location = New System.Drawing.Point(464, 192)
        Me.Button_2_Minus2.Name = "Button_2_Minus2"
        Me.Button_2_Minus2.TabIndex = 105
        Me.Button_2_Minus2.Text = "- 100"
        '
        'Button_2_Home2
        '
        Me.Button_2_Home2.Location = New System.Drawing.Point(464, 160)
        Me.Button_2_Home2.Name = "Button_2_Home2"
        Me.Button_2_Home2.TabIndex = 104
        Me.Button_2_Home2.Text = "Home"
        '
        'Button_1_Limit2
        '
        Me.Button_1_Limit2.Location = New System.Drawing.Point(352, 288)
        Me.Button_1_Limit2.Name = "Button_1_Limit2"
        Me.Button_1_Limit2.TabIndex = 103
        Me.Button_1_Limit2.Text = "Limit"
        '
        'Button_1_Plus2
        '
        Me.Button_1_Plus2.Location = New System.Drawing.Point(352, 256)
        Me.Button_1_Plus2.Name = "Button_1_Plus2"
        Me.Button_1_Plus2.TabIndex = 102
        Me.Button_1_Plus2.Text = "+ 100"
        '
        'Button_1_GOTO2
        '
        Me.Button_1_GOTO2.Location = New System.Drawing.Point(352, 224)
        Me.Button_1_GOTO2.Name = "Button_1_GOTO2"
        Me.Button_1_GOTO2.TabIndex = 101
        Me.Button_1_GOTO2.Text = "GOTO 1000"
        '
        'Button_1_Minus2
        '
        Me.Button_1_Minus2.Location = New System.Drawing.Point(352, 192)
        Me.Button_1_Minus2.Name = "Button_1_Minus2"
        Me.Button_1_Minus2.TabIndex = 100
        Me.Button_1_Minus2.Text = "- 100"
        '
        'Button_1_Home2
        '
        Me.Button_1_Home2.Location = New System.Drawing.Point(352, 160)
        Me.Button_1_Home2.Name = "Button_1_Home2"
        Me.Button_1_Home2.TabIndex = 99
        Me.Button_1_Home2.Text = "Home"
        '
        'State_2_2
        '
        Me.State_2_2.Location = New System.Drawing.Point(464, 120)
        Me.State_2_2.Name = "State_2_2"
        Me.State_2_2.Size = New System.Drawing.Size(75, 20)
        Me.State_2_2.TabIndex = 98
        Me.State_2_2.Text = "TextBox4"
        '
        'Location_2_2
        '
        Me.Location_2_2.Location = New System.Drawing.Point(464, 80)
        Me.Location_2_2.Name = "Location_2_2"
        Me.Location_2_2.Size = New System.Drawing.Size(75, 20)
        Me.Location_2_2.TabIndex = 97
        Me.Location_2_2.Text = "TextBox3"
        '
        'State_1_2
        '
        Me.State_1_2.Location = New System.Drawing.Point(352, 120)
        Me.State_1_2.Name = "State_1_2"
        Me.State_1_2.Size = New System.Drawing.Size(75, 20)
        Me.State_1_2.TabIndex = 96
        Me.State_1_2.Text = "TextBox2"
        '
        'Location_1_2
        '
        Me.Location_1_2.Location = New System.Drawing.Point(352, 80)
        Me.Location_1_2.Name = "Location_1_2"
        Me.Location_1_2.Size = New System.Drawing.Size(75, 20)
        Me.Location_1_2.TabIndex = 95
        Me.Location_1_2.Text = "TextBox1"
        '
        'Label5
        '
        Me.Label5.Location = New System.Drawing.Point(480, 40)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(56, 23)
        Me.Label5.TabIndex = 94
        Me.Label5.Text = "Axis 2"
        '
        'Label6
        '
        Me.Label6.Location = New System.Drawing.Point(368, 40)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(48, 23)
        Me.Label6.TabIndex = 93
        Me.Label6.Text = "Axis 1"
        '
        'Button_2_Limit1
        '
        Me.Button_2_Limit1.Location = New System.Drawing.Point(216, 288)
        Me.Button_2_Limit1.Name = "Button_2_Limit1"
        Me.Button_2_Limit1.TabIndex = 91
        Me.Button_2_Limit1.Text = "Limit"
        '
        'Button_2_Plus1
        '
        Me.Button_2_Plus1.Location = New System.Drawing.Point(216, 256)
        Me.Button_2_Plus1.Name = "Button_2_Plus1"
        Me.Button_2_Plus1.TabIndex = 90
        Me.Button_2_Plus1.Text = "+ 100"
        '
        'Button_2_GOTO1
        '
        Me.Button_2_GOTO1.Location = New System.Drawing.Point(216, 224)
        Me.Button_2_GOTO1.Name = "Button_2_GOTO1"
        Me.Button_2_GOTO1.TabIndex = 89
        Me.Button_2_GOTO1.Text = "GOTO 1000"
        '
        'Button_2_Minus1
        '
        Me.Button_2_Minus1.Location = New System.Drawing.Point(216, 192)
        Me.Button_2_Minus1.Name = "Button_2_Minus1"
        Me.Button_2_Minus1.TabIndex = 88
        Me.Button_2_Minus1.Text = "- 100"
        '
        'Button_2_Home1
        '
        Me.Button_2_Home1.Location = New System.Drawing.Point(216, 160)
        Me.Button_2_Home1.Name = "Button_2_Home1"
        Me.Button_2_Home1.TabIndex = 87
        Me.Button_2_Home1.Text = "Home"
        '
        'Button_1_Limit1
        '
        Me.Button_1_Limit1.Location = New System.Drawing.Point(104, 288)
        Me.Button_1_Limit1.Name = "Button_1_Limit1"
        Me.Button_1_Limit1.TabIndex = 86
        Me.Button_1_Limit1.Text = "Limit"
        '
        'Button_1_Plus1
        '
        Me.Button_1_Plus1.Location = New System.Drawing.Point(104, 256)
        Me.Button_1_Plus1.Name = "Button_1_Plus1"
        Me.Button_1_Plus1.TabIndex = 85
        Me.Button_1_Plus1.Text = "+ 100"
        '
        'Button_1_GOTO1
        '
        Me.Button_1_GOTO1.Location = New System.Drawing.Point(104, 224)
        Me.Button_1_GOTO1.Name = "Button_1_GOTO1"
        Me.Button_1_GOTO1.TabIndex = 84
        Me.Button_1_GOTO1.Text = "GOTO 1000"
        '
        'Button_1_Minus1
        '
        Me.Button_1_Minus1.Location = New System.Drawing.Point(104, 192)
        Me.Button_1_Minus1.Name = "Button_1_Minus1"
        Me.Button_1_Minus1.TabIndex = 83
        Me.Button_1_Minus1.Text = "- 100"
        '
        'Button_1_Home1
        '
        Me.Button_1_Home1.Location = New System.Drawing.Point(104, 160)
        Me.Button_1_Home1.Name = "Button_1_Home1"
        Me.Button_1_Home1.TabIndex = 82
        Me.Button_1_Home1.Text = "Home"
        '
        'State_2_1
        '
        Me.State_2_1.Location = New System.Drawing.Point(216, 120)
        Me.State_2_1.Name = "State_2_1"
        Me.State_2_1.Size = New System.Drawing.Size(75, 20)
        Me.State_2_1.TabIndex = 81
        Me.State_2_1.Text = "TextBox4"
        '
        'Location_2_1
        '
        Me.Location_2_1.Location = New System.Drawing.Point(216, 80)
        Me.Location_2_1.Name = "Location_2_1"
        Me.Location_2_1.Size = New System.Drawing.Size(75, 20)
        Me.Location_2_1.TabIndex = 80
        Me.Location_2_1.Text = "TextBox3"
        '
        'State_1_1
        '
        Me.State_1_1.Location = New System.Drawing.Point(104, 120)
        Me.State_1_1.Name = "State_1_1"
        Me.State_1_1.Size = New System.Drawing.Size(75, 20)
        Me.State_1_1.TabIndex = 79
        Me.State_1_1.Text = "TextBox2"
        '
        'Location_1_1
        '
        Me.Location_1_1.Location = New System.Drawing.Point(104, 80)
        Me.Location_1_1.Name = "Location_1_1"
        Me.Location_1_1.Size = New System.Drawing.Size(75, 20)
        Me.Location_1_1.TabIndex = 78
        Me.Location_1_1.Text = "TextBox1"
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(16, 80)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(56, 23)
        Me.Label4.TabIndex = 77
        Me.Label4.Text = "Location"
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(16, 120)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(56, 23)
        Me.Label3.TabIndex = 76
        Me.Label3.Text = "State"
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(232, 40)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(56, 23)
        Me.Label2.TabIndex = 75
        Me.Label2.Text = "Axis 2"
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(120, 40)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(48, 23)
        Me.Label1.TabIndex = 74
        Me.Label1.Text = "Axis 1"
        '
        'BrightLight1
        '
        Me.BrightLight1.Controls.Add(Me.Button_FullOn1)
        Me.BrightLight1.Controls.Add(Me.Button_Plus1)
        Me.BrightLight1.Controls.Add(Me.Button_Mid1)
        Me.BrightLight1.Controls.Add(Me.Button_Minus1)
        Me.BrightLight1.Controls.Add(Me.Button_Off1)
        Me.BrightLight1.Controls.Add(Me.Value1)
        Me.BrightLight1.Location = New System.Drawing.Point(600, 16)
        Me.BrightLight1.Name = "BrightLight1"
        Me.BrightLight1.Size = New System.Drawing.Size(152, 320)
        Me.BrightLight1.TabIndex = 110
        Me.BrightLight1.TabStop = False
        Me.BrightLight1.Text = "BrightLight 1"
        '
        'Button_FullOn1
        '
        Me.Button_FullOn1.Location = New System.Drawing.Point(40, 272)
        Me.Button_FullOn1.Name = "Button_FullOn1"
        Me.Button_FullOn1.TabIndex = 5
        Me.Button_FullOn1.Text = "Full On"
        '
        'Button_Plus1
        '
        Me.Button_Plus1.Location = New System.Drawing.Point(40, 240)
        Me.Button_Plus1.Name = "Button_Plus1"
        Me.Button_Plus1.TabIndex = 4
        Me.Button_Plus1.Text = "+ 10 %"
        '
        'Button_Mid1
        '
        Me.Button_Mid1.Location = New System.Drawing.Point(40, 208)
        Me.Button_Mid1.Name = "Button_Mid1"
        Me.Button_Mid1.TabIndex = 3
        Me.Button_Mid1.Text = " 50 %"
        '
        'Button_Minus1
        '
        Me.Button_Minus1.Location = New System.Drawing.Point(40, 176)
        Me.Button_Minus1.Name = "Button_Minus1"
        Me.Button_Minus1.TabIndex = 2
        Me.Button_Minus1.Text = "- 10 %"
        '
        'Button_Off1
        '
        Me.Button_Off1.Location = New System.Drawing.Point(40, 144)
        Me.Button_Off1.Name = "Button_Off1"
        Me.Button_Off1.TabIndex = 1
        Me.Button_Off1.Text = "Off"
        '
        'Value1
        '
        Me.Value1.Location = New System.Drawing.Point(40, 64)
        Me.Value1.Name = "Value1"
        Me.Value1.ReadOnly = True
        Me.Value1.Size = New System.Drawing.Size(75, 20)
        Me.Value1.TabIndex = 0
        Me.Value1.Text = "TextBox1"
        '
        'BrightLight2
        '
        Me.BrightLight2.Controls.Add(Me.Button_FullOn2)
        Me.BrightLight2.Controls.Add(Me.Button_Plus2)
        Me.BrightLight2.Controls.Add(Me.Button_Mid2)
        Me.BrightLight2.Controls.Add(Me.Button_Minus2)
        Me.BrightLight2.Controls.Add(Me.Button_Off2)
        Me.BrightLight2.Controls.Add(Me.Value2)
        Me.BrightLight2.Location = New System.Drawing.Point(768, 16)
        Me.BrightLight2.Name = "BrightLight2"
        Me.BrightLight2.Size = New System.Drawing.Size(160, 320)
        Me.BrightLight2.TabIndex = 111
        Me.BrightLight2.TabStop = False
        Me.BrightLight2.Text = "BrightLight 2"
        '
        'Button_FullOn2
        '
        Me.Button_FullOn2.Location = New System.Drawing.Point(48, 272)
        Me.Button_FullOn2.Name = "Button_FullOn2"
        Me.Button_FullOn2.TabIndex = 5
        Me.Button_FullOn2.Text = "Full On"
        '
        'Button_Plus2
        '
        Me.Button_Plus2.Location = New System.Drawing.Point(48, 240)
        Me.Button_Plus2.Name = "Button_Plus2"
        Me.Button_Plus2.TabIndex = 4
        Me.Button_Plus2.Text = "+ 10 %"
        '
        'Button_Mid2
        '
        Me.Button_Mid2.Location = New System.Drawing.Point(48, 208)
        Me.Button_Mid2.Name = "Button_Mid2"
        Me.Button_Mid2.TabIndex = 3
        Me.Button_Mid2.Text = " 50 %"
        '
        'Button_Minus2
        '
        Me.Button_Minus2.Location = New System.Drawing.Point(48, 176)
        Me.Button_Minus2.Name = "Button_Minus2"
        Me.Button_Minus2.TabIndex = 2
        Me.Button_Minus2.Text = "- 10 %"
        '
        'Button_Off2
        '
        Me.Button_Off2.Location = New System.Drawing.Point(48, 144)
        Me.Button_Off2.Name = "Button_Off2"
        Me.Button_Off2.TabIndex = 1
        Me.Button_Off2.Text = "Off"
        '
        'Value2
        '
        Me.Value2.Location = New System.Drawing.Point(48, 64)
        Me.Value2.Name = "Value2"
        Me.Value2.ReadOnly = True
        Me.Value2.Size = New System.Drawing.Size(75, 20)
        Me.Value2.TabIndex = 0
        Me.Value2.Text = "TextBox1"
        '
        'Timer1
        '
        '
        'Motor1
        '
        Me.Motor1.Location = New System.Drawing.Point(88, 16)
        Me.Motor1.Name = "Motor1"
        Me.Motor1.Size = New System.Drawing.Size(224, 320)
        Me.Motor1.TabIndex = 112
        Me.Motor1.TabStop = False
        Me.Motor1.Text = "Motor1"
        '
        'Motor2
        '
        Me.Motor2.Location = New System.Drawing.Point(336, 16)
        Me.Motor2.Name = "Motor2"
        Me.Motor2.Size = New System.Drawing.Size(224, 320)
        Me.Motor2.TabIndex = 113
        Me.Motor2.TabStop = False
        Me.Motor2.Text = "Motor2"
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(992, 389)
        Me.Controls.Add(Me.BrightLight1)
        Me.Controls.Add(Me.BrightLight2)
        Me.Controls.Add(Me.Button_2_Limit2)
        Me.Controls.Add(Me.Button_2_Plus2)
        Me.Controls.Add(Me.Button_2_GOTO2)
        Me.Controls.Add(Me.Button_2_Minus2)
        Me.Controls.Add(Me.Button_2_Home2)
        Me.Controls.Add(Me.Button_1_Limit2)
        Me.Controls.Add(Me.Button_1_Plus2)
        Me.Controls.Add(Me.Button_1_GOTO2)
        Me.Controls.Add(Me.Button_1_Minus2)
        Me.Controls.Add(Me.Button_1_Home2)
        Me.Controls.Add(Me.State_2_2)
        Me.Controls.Add(Me.Location_2_2)
        Me.Controls.Add(Me.State_1_2)
        Me.Controls.Add(Me.Location_1_2)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.Button_2_Limit1)
        Me.Controls.Add(Me.Button_2_Plus1)
        Me.Controls.Add(Me.Button_2_GOTO1)
        Me.Controls.Add(Me.Button_2_Minus1)
        Me.Controls.Add(Me.Button_2_Home1)
        Me.Controls.Add(Me.Button_1_Limit1)
        Me.Controls.Add(Me.Button_1_Plus1)
        Me.Controls.Add(Me.Button_1_GOTO1)
        Me.Controls.Add(Me.Button_1_Minus1)
        Me.Controls.Add(Me.Button_1_Home1)
        Me.Controls.Add(Me.State_2_1)
        Me.Controls.Add(Me.Location_2_1)
        Me.Controls.Add(Me.State_1_1)
        Me.Controls.Add(Me.Location_1_1)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Motor1)
        Me.Controls.Add(Me.Motor2)
        Me.Name = "Form1"
        Me.Text = "Motor1"
        Me.BrightLight1.ResumeLayout(False)
        Me.BrightLight2.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

#End Region


    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        temp = 0
        SerConnectionRead(serHandle1, REG_USER_STATUS_1, temp)            ' read motor state
        State_1_1.Text = temp

        temp = 0
        SerConnectionRead(serHandle1, REG_USER_CURRENT_1, temp)           ' read motor location
        Location_1_1.Text() = temp

        temp = 0
        SerConnectionRead(serHandle1, REG_USER_STATUS_2, temp)            ' read motor state
        State_2_1.Text = temp

        temp = 0
        SerConnectionRead(serHandle1, REG_USER_CURRENT_2, temp)           ' read motor location
        Location_2_1.Text() = temp


        temp = 0
        SerConnectionRead(serHandle2, REG_USER_STATUS_1, temp)            ' read motor state
        State_1_2.Text = temp

        temp = 0
        SerConnectionRead(serHandle2, REG_USER_CURRENT_1, temp)           ' read motor location
        Location_1_2.Text() = temp

        temp = 0
        SerConnectionRead(serHandle2, REG_USER_STATUS_2, temp)            ' read motor state
        State_2_2.Text = temp

        temp = 0
        SerConnectionRead(serHandle2, REG_USER_CURRENT_2, temp)           ' read motor location
        Location_2_2.Text() = temp


        temp = 0
        SerConnectionRead(serHandle3, REG_PWM_ABSOLUTE, temp)            ' read brightlight 1
        Value1.Text() = temp / 10

        temp = 0
        SerConnectionRead(serHandle4, REG_PWM_ABSOLUTE, temp)            ' read brightlight 1
        Value2.Text() = temp / 10

    End Sub

    Private Sub Button_1_Home1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Home1.Click
        temp = 0
        SerConnectionWrite(serHandle1, REG_USER_LIMIT_1, temp)

    End Sub

    Private Sub Button_1_Minus1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Minus1.Click
        temp = -100
        SerConnectionWrite(serHandle1, REG_USER_INCREMENT_1, temp)

    End Sub

    Private Sub Button_1_GOTO1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_GOTO1.Click
        temp = 1000
        SerConnectionWrite(serHandle1, REG_USER_TARGET_1, temp)

    End Sub

    Private Sub Button_1_Plus1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Plus1.Click
        temp = 100
        SerConnectionWrite(serHandle1, REG_USER_INCREMENT_1, temp)

    End Sub

    Private Sub Button_1_Limit1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Limit1.Click
        temp = 1
        SerConnectionWrite(serHandle1, REG_USER_LIMIT_1, temp)

    End Sub

    Private Sub Button_2_Home1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Home1.Click
        temp = 0
        SerConnectionWrite(serHandle1, REG_USER_LIMIT_2, temp)

    End Sub

    Private Sub Button_2_Minus1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Minus1.Click
        temp = -100
        SerConnectionWrite(serHandle1, REG_USER_INCREMENT_2, temp)

    End Sub

    Private Sub Button_2_GOTO1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_GOTO1.Click
        temp = 1000
        SerConnectionWrite(serHandle1, REG_USER_TARGET_2, temp)

    End Sub

    Private Sub Button_2_Plus1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Plus1.Click
        temp = 100
        SerConnectionWrite(serHandle1, REG_USER_INCREMENT_2, temp)

    End Sub

    Private Sub Button_2_Limit1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Limit1.Click
        temp = 1
        SerConnectionWrite(serHandle1, REG_USER_LIMIT_2, temp)

    End Sub

    Private Sub Button_1_Home2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Home2.Click
        temp = 0
        SerConnectionWrite(serHandle2, REG_USER_LIMIT_1, temp)

    End Sub

    Private Sub Button_1_Minus2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Minus2.Click
        temp = -100
        SerConnectionWrite(serHandle2, REG_USER_INCREMENT_1, temp)

    End Sub

    Private Sub Button_1_GOTO2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_GOTO2.Click
        temp = 1000
        SerConnectionWrite(serHandle2, REG_USER_TARGET_1, temp)

    End Sub

    Private Sub Button_1_Plus2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Plus2.Click
        temp = 100
        SerConnectionWrite(serHandle2, REG_USER_INCREMENT_1, temp)

    End Sub

    Private Sub Button_1_Limit2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Limit2.Click
        temp = 1
        SerConnectionWrite(serHandle2, REG_USER_LIMIT_1, temp)

    End Sub

    Private Sub Button_2_Home2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Home2.Click
        temp = 0
        SerConnectionWrite(serHandle2, REG_USER_LIMIT_2, temp)

    End Sub

    Private Sub Button_2_Minus2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Minus2.Click
        temp = -100
        SerConnectionWrite(serHandle2, REG_USER_INCREMENT_2, temp)

    End Sub

    Private Sub Button_2_GOTO2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_GOTO2.Click
        temp = 1000
        SerConnectionWrite(serHandle2, REG_USER_TARGET_2, temp)

    End Sub

    Private Sub Button_2_Plus2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Plus2.Click
        temp = 100
        SerConnectionWrite(serHandle2, REG_USER_INCREMENT_2, temp)

    End Sub

    Private Sub Button_2_Limit2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Limit2.Click
        temp = 1
        SerConnectionWrite(serHandle2, REG_USER_LIMIT_2, temp)

    End Sub

    Private Sub Button_Off1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Off1.Click
        temp = 0
        SerConnectionWrite(serHandle3, REG_PWM_ABSOLUTE, temp)

    End Sub

    Private Sub Button_Minus1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Minus1.Click
        temp = -100
        SerConnectionWrite(serHandle3, REG_PWM_INCREMENT, temp)

    End Sub

    Private Sub Button_Mid1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Mid1.Click
        temp = 500
        SerConnectionWrite(serHandle3, REG_PWM_ABSOLUTE, temp)

    End Sub

    Private Sub Button_Plus1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Plus1.Click
        temp = +100
        SerConnectionWrite(serHandle3, REG_PWM_INCREMENT, temp)

    End Sub

    Private Sub Button_FullOn1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_FullOn1.Click
        temp = 1000
        SerConnectionWrite(serHandle3, REG_PWM_ABSOLUTE, temp)

    End Sub

    Private Sub Button_Off2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Off2.Click
        temp = 0
        SerConnectionWrite(serHandle4, REG_PWM_ABSOLUTE, temp)

    End Sub

    Private Sub Button_Minus2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Minus2.Click
        temp = -100
        SerConnectionWrite(serHandle4, REG_PWM_INCREMENT, temp)

    End Sub

    Private Sub Button_Mid2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Mid2.Click
        temp = 500
        SerConnectionWrite(serHandle4, REG_PWM_ABSOLUTE, temp)

    End Sub

    Private Sub Button_Plus2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Plus2.Click
        temp = +100
        SerConnectionWrite(serHandle4, REG_PWM_INCREMENT, temp)

    End Sub

    Private Sub Button_FullOn2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_FullOn2.Click
        temp = 1000
        SerConnectionWrite(serHandle4, REG_PWM_ABSOLUTE, temp)

    End Sub
End Class
