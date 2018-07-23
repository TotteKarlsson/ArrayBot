Public Class Form1
    Inherits System.Windows.Forms.Form

    Public usbHandle1 As Integer    ' motor 1
    Public usbHandle2 As Integer    ' motor 2
    Public usbHandle3 As Integer    ' brightlight 1
    Public usbHandle4 As Integer    ' brightlight 2
    Public usbFirst1 As Integer
    Public usbFirst2 As Integer
    Public usbFirst3 As Integer
    Public usbFirst4 As Integer
    Public usbType1 As Integer
    Public usbType2 As Integer

    Public temp As Integer



#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

        Static errorConnect As Boolean
        errorConnect = False
        Do
            Dim errorString As String
            errorString = ""
            errorConnect = False

            ' find all the brightlights on the USB chain
            USBFindUSBinterfaces()
            ' connect to the 1st motor found 
            usbHandle1 = USBConnectionConnect(1, DEF_MOTOR_CONTROLLER)      ' connect to motor 1
            ' connect to the 2nd motor controller found 
            usbHandle2 = USBConnectionConnect(2, DEF_MOTOR_CONTROLLER)      ' connect Motor controller 2

            ' connect to the 1st motor found 
            'usbHandle1 = USBConnectionConnectSpec(1, DEF_MOTOR_CONTROLLER, DEF_MICROMO2PHASE)     ' connect to motor 1
            ' connect to the 2nd motor controller found 
            'usbHandle2 = USBConnectionConnectSpec(1, DEF_MOTOR_CONTROLLER, DEF_VEXTA5PHASE)     ' connect Motor controller 2
            ' connect to the 1st brightlight found 

            usbHandle3 = USBConnectionConnect(1, DEF_BRIGHTLIGHT)           ' connect to  brightlight 1
            ' connect to the 2nd brightlight found 
            usbHandle4 = USBConnectionConnect(2, DEF_BRIGHTLIGHT)           ' connect to  brightlight 2

            If usbHandle1 = &H100 Then
                errorString = errorString + "USB motor 1 did not open or connect" & ControlChars.CrLf
                errorConnect = True
            End If
            If usbHandle2 = &H100 Then
                errorString = errorString + "USB motor 2 did not open or connect" & ControlChars.CrLf
                errorConnect = True
            End If
            If usbHandle3 = &H100 Then
                errorString = errorString + "USB brightlight 1 did not open or connect" & ControlChars.CrLf
                errorConnect = True
            End If
            If usbHandle4 = &H100 Then
                errorString = errorString + "USB brightlight 2 did not open or connect" & ControlChars.CrLf
                errorConnect = True
            End If

            If (errorConnect) Then

                Dim response As MsgBoxResult
                response = MsgBox(errorString, MsgBoxStyle.AbortRetryIgnore)
                If response = MsgBoxResult.Retry Then   ' User chose Yes.
                    ' let the while loop repeat
                ElseIf response = MsgBoxResult.Ignore Then
                    Exit Do
                Else
                    Throw New System.Exception("Program Canceled")
                End If
            End If
        Loop While (errorConnect)

        USBConnectionRead(usbHandle1, REG_SYS_PRODUCTID_SUBCLASS, usbType1)            ' find out what kind of controller

        Select Case usbType1
            Case 1
                MotorType1.Text = "MicroMo Stepper"
            Case 2
                MotorType1.Text = "Vexta 5-Phase "
            Case 3
                MotorType1.Text = "2-Axis DC"
            Case Else
                MotorType1.Text = "MicroMo Stepper"
        End Select

        If usbHandle1 = &H100 Then
            MotorType1.Text = "no motor"
        End If



        USBConnectionRead(usbHandle1, REG_USER_STATUS_1, temp)            ' read motor state
        State_1_1.Text = temp

        USBConnectionRead(usbHandle1, REG_USER_CURRENT_1, temp)            ' read motor location
        Location_1_1.Text() = temp

        USBConnectionRead(usbHandle1, REG_USER_STATUS_1, temp)            ' read motor state
        State_2_1.Text = temp

        USBConnectionRead(usbHandle1, REG_USER_CURRENT_1, temp)            ' read motor location
        Location_2_1.Text() = temp


        USBConnectionRead(usbHandle2, REG_SYS_PRODUCTID_SUBCLASS, usbType2)            ' find out what kind of controller

        Select Case usbType2
            Case 1
                MotorType2.Text = "MicroMo Stepper"
            Case 2
                MotorType2.Text = "Vexta 5-Phase "
            Case 3
                MotorType2.Text = "2-Axis DC"
            Case Else
                MotorType2.Text = "MicroMo Stepper"
        End Select

        If usbHandle2 = &H100 Then
            MotorType2.Text = "no motor"
        End If


        USBConnectionRead(usbHandle2, REG_USER_STATUS_2, temp)            ' read motor state
        State_1_2.Text = temp

        USBConnectionRead(usbHandle2, REG_USER_CURRENT_2, temp)            ' read motor location
        Location_1_2.Text() = temp

        USBConnectionRead(usbHandle2, REG_USER_STATUS_2, temp)            ' read motor state
        State_2_2.Text = temp

        USBConnectionRead(usbHandle2, REG_USER_CURRENT_2, temp)            ' read motor location
        Location_2_2.Text() = temp


        If usbHandle3 = &H100 Then
            BrightLight1.Text = "no brightlight"
        End If


        USBConnectionRead(usbHandle3, REG_PWM_ABSOLUTE, temp)            ' read brightlight 1
        Value1.Text = temp

        If usbHandle4 = &H100 Then
            BrightLight2.Text = "no brightlight"
        End If

        USBConnectionRead(usbHandle4, REG_PWM_ABSOLUTE, temp)            ' read brightlight 2
        Value2.Text = temp

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
    Friend WithEvents State_2_2 As System.Windows.Forms.TextBox
    Friend WithEvents Location_2_2 As System.Windows.Forms.TextBox
    Friend WithEvents State_1_2 As System.Windows.Forms.TextBox
    Friend WithEvents Location_1_2 As System.Windows.Forms.TextBox
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents Button_2_Home2 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Home2 As System.Windows.Forms.Button
    Friend WithEvents Button_2_Minus2 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Minus2 As System.Windows.Forms.Button
    Friend WithEvents Button_2_Limit2 As System.Windows.Forms.Button
    Friend WithEvents Button_2_Plus2 As System.Windows.Forms.Button
    Friend WithEvents Button_2_GOTO2 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Limit2 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Plus2 As System.Windows.Forms.Button
    Friend WithEvents Button_1_GOTO2 As System.Windows.Forms.Button
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
    Friend WithEvents MotorType1 As System.Windows.Forms.GroupBox
    Friend WithEvents MotorType2 As System.Windows.Forms.GroupBox
    Friend WithEvents BrightLight1 As System.Windows.Forms.GroupBox
    Friend WithEvents BrightLight2 As System.Windows.Forms.GroupBox
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
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
        Me.MotorType1 = New System.Windows.Forms.GroupBox
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
        Me.MotorType2 = New System.Windows.Forms.GroupBox
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
        Me.BrightLight1.SuspendLayout()
        Me.BrightLight2.SuspendLayout()
        Me.SuspendLayout()
        '
        'Button_2_Limit1
        '
        Me.Button_2_Limit1.Location = New System.Drawing.Point(208, 280)
        Me.Button_2_Limit1.Name = "Button_2_Limit1"
        Me.Button_2_Limit1.TabIndex = 55
        Me.Button_2_Limit1.Text = "Limit"
        '
        'Button_2_Plus1
        '
        Me.Button_2_Plus1.Location = New System.Drawing.Point(208, 248)
        Me.Button_2_Plus1.Name = "Button_2_Plus1"
        Me.Button_2_Plus1.TabIndex = 54
        Me.Button_2_Plus1.Text = "+ 100"
        '
        'Button_2_GOTO1
        '
        Me.Button_2_GOTO1.Location = New System.Drawing.Point(208, 216)
        Me.Button_2_GOTO1.Name = "Button_2_GOTO1"
        Me.Button_2_GOTO1.TabIndex = 53
        Me.Button_2_GOTO1.Text = "GOTO 1000"
        '
        'Button_2_Minus1
        '
        Me.Button_2_Minus1.Location = New System.Drawing.Point(208, 184)
        Me.Button_2_Minus1.Name = "Button_2_Minus1"
        Me.Button_2_Minus1.TabIndex = 52
        Me.Button_2_Minus1.Text = "- 100"
        '
        'Button_2_Home1
        '
        Me.Button_2_Home1.Location = New System.Drawing.Point(208, 152)
        Me.Button_2_Home1.Name = "Button_2_Home1"
        Me.Button_2_Home1.TabIndex = 51
        Me.Button_2_Home1.Text = "Home"
        '
        'Button_1_Limit1
        '
        Me.Button_1_Limit1.Location = New System.Drawing.Point(96, 280)
        Me.Button_1_Limit1.Name = "Button_1_Limit1"
        Me.Button_1_Limit1.TabIndex = 50
        Me.Button_1_Limit1.Text = "Limit"
        '
        'Button_1_Plus1
        '
        Me.Button_1_Plus1.Location = New System.Drawing.Point(96, 248)
        Me.Button_1_Plus1.Name = "Button_1_Plus1"
        Me.Button_1_Plus1.TabIndex = 49
        Me.Button_1_Plus1.Text = "+ 100"
        '
        'Button_1_GOTO1
        '
        Me.Button_1_GOTO1.Location = New System.Drawing.Point(96, 216)
        Me.Button_1_GOTO1.Name = "Button_1_GOTO1"
        Me.Button_1_GOTO1.TabIndex = 48
        Me.Button_1_GOTO1.Text = "GOTO 1000"
        '
        'Button_1_Minus1
        '
        Me.Button_1_Minus1.Location = New System.Drawing.Point(96, 184)
        Me.Button_1_Minus1.Name = "Button_1_Minus1"
        Me.Button_1_Minus1.TabIndex = 47
        Me.Button_1_Minus1.Text = "- 100"
        '
        'Button_1_Home1
        '
        Me.Button_1_Home1.Location = New System.Drawing.Point(96, 152)
        Me.Button_1_Home1.Name = "Button_1_Home1"
        Me.Button_1_Home1.TabIndex = 46
        Me.Button_1_Home1.Text = "Home"
        '
        'State_2_1
        '
        Me.State_2_1.Location = New System.Drawing.Point(208, 112)
        Me.State_2_1.Name = "State_2_1"
        Me.State_2_1.Size = New System.Drawing.Size(75, 20)
        Me.State_2_1.TabIndex = 45
        Me.State_2_1.Text = "TextBox4"
        '
        'Location_2_1
        '
        Me.Location_2_1.Location = New System.Drawing.Point(208, 72)
        Me.Location_2_1.Name = "Location_2_1"
        Me.Location_2_1.Size = New System.Drawing.Size(75, 20)
        Me.Location_2_1.TabIndex = 44
        Me.Location_2_1.Text = "TextBox3"
        '
        'State_1_1
        '
        Me.State_1_1.Location = New System.Drawing.Point(96, 112)
        Me.State_1_1.Name = "State_1_1"
        Me.State_1_1.Size = New System.Drawing.Size(75, 20)
        Me.State_1_1.TabIndex = 43
        Me.State_1_1.Text = "TextBox2"
        '
        'Location_1_1
        '
        Me.Location_1_1.Location = New System.Drawing.Point(96, 72)
        Me.Location_1_1.Name = "Location_1_1"
        Me.Location_1_1.Size = New System.Drawing.Size(75, 20)
        Me.Location_1_1.TabIndex = 42
        Me.Location_1_1.Text = "TextBox1"
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(8, 72)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(56, 23)
        Me.Label4.TabIndex = 41
        Me.Label4.Text = "Location"
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(8, 112)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(56, 23)
        Me.Label3.TabIndex = 40
        Me.Label3.Text = "State"
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(224, 32)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(56, 23)
        Me.Label2.TabIndex = 39
        Me.Label2.Text = "Axis 2"
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(112, 32)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(48, 23)
        Me.Label1.TabIndex = 38
        Me.Label1.Text = "Axis 1"
        '
        'MotorType1
        '
        Me.MotorType1.Location = New System.Drawing.Point(72, 8)
        Me.MotorType1.Name = "MotorType1"
        Me.MotorType1.Size = New System.Drawing.Size(232, 320)
        Me.MotorType1.TabIndex = 56
        Me.MotorType1.TabStop = False
        Me.MotorType1.Text = "Motor 1"
        '
        'Button_2_Limit2
        '
        Me.Button_2_Limit2.Location = New System.Drawing.Point(456, 280)
        Me.Button_2_Limit2.Name = "Button_2_Limit2"
        Me.Button_2_Limit2.TabIndex = 72
        Me.Button_2_Limit2.Text = "Limit"
        '
        'Button_2_Plus2
        '
        Me.Button_2_Plus2.Location = New System.Drawing.Point(456, 248)
        Me.Button_2_Plus2.Name = "Button_2_Plus2"
        Me.Button_2_Plus2.TabIndex = 71
        Me.Button_2_Plus2.Text = "+ 100"
        '
        'Button_2_GOTO2
        '
        Me.Button_2_GOTO2.Location = New System.Drawing.Point(456, 216)
        Me.Button_2_GOTO2.Name = "Button_2_GOTO2"
        Me.Button_2_GOTO2.TabIndex = 70
        Me.Button_2_GOTO2.Text = "GOTO 1000"
        '
        'Button_2_Minus2
        '
        Me.Button_2_Minus2.Location = New System.Drawing.Point(456, 184)
        Me.Button_2_Minus2.Name = "Button_2_Minus2"
        Me.Button_2_Minus2.TabIndex = 69
        Me.Button_2_Minus2.Text = "- 100"
        '
        'Button_2_Home2
        '
        Me.Button_2_Home2.Location = New System.Drawing.Point(456, 152)
        Me.Button_2_Home2.Name = "Button_2_Home2"
        Me.Button_2_Home2.TabIndex = 68
        Me.Button_2_Home2.Text = "Home"
        '
        'Button_1_Limit2
        '
        Me.Button_1_Limit2.Location = New System.Drawing.Point(344, 280)
        Me.Button_1_Limit2.Name = "Button_1_Limit2"
        Me.Button_1_Limit2.TabIndex = 67
        Me.Button_1_Limit2.Text = "Limit"
        '
        'Button_1_Plus2
        '
        Me.Button_1_Plus2.Location = New System.Drawing.Point(344, 248)
        Me.Button_1_Plus2.Name = "Button_1_Plus2"
        Me.Button_1_Plus2.TabIndex = 66
        Me.Button_1_Plus2.Text = "+ 100"
        '
        'Button_1_GOTO2
        '
        Me.Button_1_GOTO2.Location = New System.Drawing.Point(344, 216)
        Me.Button_1_GOTO2.Name = "Button_1_GOTO2"
        Me.Button_1_GOTO2.TabIndex = 65
        Me.Button_1_GOTO2.Text = "GOTO 1000"
        '
        'Button_1_Minus2
        '
        Me.Button_1_Minus2.Location = New System.Drawing.Point(344, 184)
        Me.Button_1_Minus2.Name = "Button_1_Minus2"
        Me.Button_1_Minus2.TabIndex = 64
        Me.Button_1_Minus2.Text = "- 100"
        '
        'Button_1_Home2
        '
        Me.Button_1_Home2.Location = New System.Drawing.Point(344, 152)
        Me.Button_1_Home2.Name = "Button_1_Home2"
        Me.Button_1_Home2.TabIndex = 63
        Me.Button_1_Home2.Text = "Home"
        '
        'State_2_2
        '
        Me.State_2_2.Location = New System.Drawing.Point(456, 112)
        Me.State_2_2.Name = "State_2_2"
        Me.State_2_2.Size = New System.Drawing.Size(75, 20)
        Me.State_2_2.TabIndex = 62
        Me.State_2_2.Text = "TextBox4"
        '
        'Location_2_2
        '
        Me.Location_2_2.Location = New System.Drawing.Point(456, 72)
        Me.Location_2_2.Name = "Location_2_2"
        Me.Location_2_2.Size = New System.Drawing.Size(75, 20)
        Me.Location_2_2.TabIndex = 61
        Me.Location_2_2.Text = "TextBox3"
        '
        'State_1_2
        '
        Me.State_1_2.Location = New System.Drawing.Point(344, 112)
        Me.State_1_2.Name = "State_1_2"
        Me.State_1_2.Size = New System.Drawing.Size(75, 20)
        Me.State_1_2.TabIndex = 60
        Me.State_1_2.Text = "TextBox2"
        '
        'Location_1_2
        '
        Me.Location_1_2.Location = New System.Drawing.Point(344, 72)
        Me.Location_1_2.Name = "Location_1_2"
        Me.Location_1_2.Size = New System.Drawing.Size(75, 20)
        Me.Location_1_2.TabIndex = 59
        Me.Location_1_2.Text = "TextBox1"
        '
        'Label5
        '
        Me.Label5.Location = New System.Drawing.Point(472, 32)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(56, 23)
        Me.Label5.TabIndex = 58
        Me.Label5.Text = "Axis 2"
        '
        'Label6
        '
        Me.Label6.Location = New System.Drawing.Point(360, 32)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(48, 23)
        Me.Label6.TabIndex = 57
        Me.Label6.Text = "Axis 1"
        '
        'MotorType2
        '
        Me.MotorType2.Location = New System.Drawing.Point(320, 8)
        Me.MotorType2.Name = "MotorType2"
        Me.MotorType2.Size = New System.Drawing.Size(232, 320)
        Me.MotorType2.TabIndex = 73
        Me.MotorType2.TabStop = False
        Me.MotorType2.Text = "Motor 2"
        '
        'BrightLight1
        '
        Me.BrightLight1.Controls.Add(Me.Button_FullOn1)
        Me.BrightLight1.Controls.Add(Me.Button_Plus1)
        Me.BrightLight1.Controls.Add(Me.Button_Mid1)
        Me.BrightLight1.Controls.Add(Me.Button_Minus1)
        Me.BrightLight1.Controls.Add(Me.Button_Off1)
        Me.BrightLight1.Controls.Add(Me.Value1)
        Me.BrightLight1.Location = New System.Drawing.Point(600, 8)
        Me.BrightLight1.Name = "BrightLight1"
        Me.BrightLight1.Size = New System.Drawing.Size(152, 320)
        Me.BrightLight1.TabIndex = 74
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
        Me.BrightLight2.Location = New System.Drawing.Point(768, 8)
        Me.BrightLight2.Name = "BrightLight2"
        Me.BrightLight2.Size = New System.Drawing.Size(160, 320)
        Me.BrightLight2.TabIndex = 75
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
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(944, 381)
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
        Me.Controls.Add(Me.State_2_1)
        Me.Controls.Add(Me.Location_2_1)
        Me.Controls.Add(Me.State_1_1)
        Me.Controls.Add(Me.Location_1_1)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.MotorType2)
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
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.MotorType1)
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.BrightLight1.ResumeLayout(False)
        Me.BrightLight2.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        temp = 0
        USBConnectionRead(usbHandle1, REG_USER_STATUS_1, temp)            ' read motor state
        State_1_1.Text = temp

        temp = 0
        USBConnectionRead(usbHandle1, REG_USER_CURRENT_1, temp)           ' read motor location
        Location_1_1.Text() = temp

        temp = 0
        USBConnectionRead(usbHandle1, REG_USER_STATUS_2, temp)            ' read motor state
        State_2_1.Text = temp

        temp = 0
        USBConnectionRead(usbHandle1, REG_USER_CURRENT_2, temp)           ' read motor location
        Location_2_1.Text() = temp


        temp = 0
        USBConnectionRead(usbHandle2, REG_USER_STATUS_1, temp)            ' read motor state
        State_1_2.Text = temp

        temp = 0
        USBConnectionRead(usbHandle2, REG_USER_CURRENT_1, temp)           ' read motor location
        Location_1_2.Text() = temp

        temp = 0
        USBConnectionRead(usbHandle2, REG_USER_STATUS_2, temp)            ' read motor state
        State_2_2.Text = temp

        temp = 0
        USBConnectionRead(usbHandle2, REG_USER_CURRENT_2, temp)           ' read motor location
        Location_2_2.Text() = temp


        temp = 0
        USBConnectionRead(usbHandle3, REG_PWM_ABSOLUTE, temp)            ' read brightlight 1 value
        Value1.Text() = temp / 10

        temp = 0
        USBConnectionRead(usbHandle4, REG_PWM_ABSOLUTE, temp)            ' read brightlight 2 value
        Value2.Text() = temp / 10

    End Sub

    Private Sub Button_1_Home1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Home1.Click
        temp = 0
        USBConnectionWrite(usbHandle1, REG_USER_LIMIT_1, temp)

    End Sub

    Private Sub Button_1_Minus1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Minus1.Click
        temp = -100
        USBConnectionWrite(usbHandle1, REG_USER_INCREMENT_1, temp)

    End Sub

    Private Sub Button_1_GOTO1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_GOTO1.Click
        temp = 1000
        USBConnectionWrite(usbHandle1, REG_USER_TARGET_1, temp)

    End Sub

    Private Sub Button_1_Plus1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Plus1.Click
        temp = +100
        USBConnectionWrite(usbHandle1, REG_USER_INCREMENT_1, temp)

    End Sub

    Private Sub Button_1_Limit1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Limit1.Click
        temp = 1
        USBConnectionWrite(usbHandle1, REG_USER_LIMIT_1, temp)

    End Sub

    Private Sub Button_2_Home1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Home1.Click
        temp = 0
        USBConnectionWrite(usbHandle1, REG_USER_LIMIT_2, temp)

    End Sub

    Private Sub Button_2_Minus1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Minus1.Click
        temp = -100
        USBConnectionWrite(usbHandle1, REG_USER_INCREMENT_2, temp)

    End Sub
    Private Sub Button_2_GOTO1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_GOTO1.Click
        temp = 1000
        USBConnectionWrite(usbHandle1, REG_USER_TARGET_2, temp)

    End Sub

    Private Sub Button_2_Plus1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Plus1.Click
        temp = +100
        USBConnectionWrite(usbHandle1, REG_USER_INCREMENT_2, temp)

    End Sub

    Private Sub Button_2_Limit1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Limit1.Click
        temp = 1
        USBConnectionWrite(usbHandle1, REG_USER_LIMIT_2, temp)

    End Sub
    Private Sub Button_1_Home2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Home2.Click
        temp = 0
        USBConnectionWrite(usbHandle2, REG_USER_LIMIT_1, temp)

    End Sub
    Private Sub Button_1_Minus2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Minus2.Click
        temp = -100
        USBConnectionWrite(usbHandle2, REG_USER_INCREMENT_1, temp)
    End Sub

    Private Sub Button_1_GOTO2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_GOTO2.Click
        temp = 1000
        USBConnectionWrite(usbHandle2, REG_USER_TARGET_1, temp)

    End Sub

    Private Sub Button_1_Plus2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Plus2.Click
        temp = +100
        USBConnectionWrite(usbHandle2, REG_USER_INCREMENT_1, temp)

    End Sub

    Private Sub Button_1_Limit2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Limit2.Click
        temp = 1
        USBConnectionWrite(usbHandle2, REG_USER_LIMIT_1, temp)

    End Sub

    Private Sub Button_2_Home2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Home2.Click
        temp = 0
        USBConnectionWrite(usbHandle2, REG_USER_LIMIT_2, temp)

    End Sub

    Private Sub Button_2_Minus2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Minus2.Click
        temp = -100
        USBConnectionWrite(usbHandle2, REG_USER_INCREMENT_2, temp)

    End Sub

    Private Sub Button_2_GOTO2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_GOTO2.Click
        temp = 1000
        USBConnectionWrite(usbHandle2, REG_USER_TARGET_2, temp)

    End Sub

    Private Sub Button_2_Plus2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Plus2.Click
        temp = +100
        USBConnectionWrite(usbHandle2, REG_USER_INCREMENT_2, temp)

    End Sub

    Private Sub Button_2_Limit2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Limit2.Click
        temp = 1
        USBConnectionWrite(usbHandle2, REG_USER_LIMIT_2, temp)

    End Sub

    Private Sub Button_Off1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Off1.Click
        temp = 0
        USBConnectionWrite(usbHandle3, REG_PWM_ABSOLUTE, temp)

    End Sub

    Private Sub Button_Minus1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Minus1.Click
        temp = -100
        USBConnectionWrite(usbHandle3, REG_PWM_INCREMENT, temp)

    End Sub

    Private Sub Button_Mid1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Mid1.Click
        temp = 500
        USBConnectionWrite(usbHandle3, REG_PWM_ABSOLUTE, temp)

    End Sub

    Private Sub Button_Plus1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Plus1.Click
        temp = +100
        USBConnectionWrite(usbHandle3, REG_PWM_INCREMENT, temp)

    End Sub

    Private Sub Button_FullOn1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_FullOn1.Click
        temp = 1000
        USBConnectionWrite(usbHandle3, REG_PWM_ABSOLUTE, temp)

    End Sub

    Private Sub Button_Off2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Off2.Click
        temp = 0
        USBConnectionWrite(usbHandle4, REG_PWM_ABSOLUTE, temp)

    End Sub

    Private Sub Button_Minus2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Minus2.Click
        temp = -100
        USBConnectionWrite(usbHandle4, REG_PWM_INCREMENT, temp)

    End Sub

    Private Sub Button_Mid2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Mid2.Click
        temp = 500
        USBConnectionWrite(usbHandle4, REG_PWM_ABSOLUTE, temp)

    End Sub

    Private Sub Button_Plus2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Plus2.Click
        temp = +100
        USBConnectionWrite(usbHandle4, REG_PWM_INCREMENT, temp)

    End Sub

    Private Sub Button_FullOn2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_FullOn2.Click
        temp = 1000
        USBConnectionWrite(usbHandle4, REG_PWM_ABSOLUTE, temp)

    End Sub


End Class
