Public Class Form1
    Inherits System.Windows.Forms.Form
    Public serHandle1 As Integer    ' motor 1
    Public serHandle2 As Integer    ' motor 2
    Public serHandle3 As Integer    ' brightlight 1
    Public serHandle4 As Integer    ' brightlight 2

    Public serType1 As Integer
    Public serType2 As Integer

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

        SerConnectionRead(serHandle1, REG_SYS_PRODUCTID_SUBCLASS, serType1)            ' find out what kind of controller

        Select Case serType1
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





        ' connect to the brightlight on COM2
        serHandle3 = SerConnectionConnect(2, DEF_BRIGHTLIGHT)         ' connect to port 3, brightlight 1

        While serHandle3 = &H0
            Dim response As MsgBoxResult
            response = MsgBox("COM PORT 2 did not open or connect", MsgBoxStyle.AbortRetryIgnore)
            If response = MsgBoxResult.Retry Then   ' User chose Yes.
                serHandle1 = SerConnectionConnect(2, DEF_BRIGHTLIGHT)   ' connect to port 3, brightlight 1
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
    Friend WithEvents Button_1_Limit1 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Plus1 As System.Windows.Forms.Button
    Friend WithEvents Button_1_GOTO1 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Minus1 As System.Windows.Forms.Button
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
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents Button_1_Home1 As System.Windows.Forms.Button
    Friend WithEvents Motor1 As System.Windows.Forms.GroupBox
    Friend WithEvents Brightlight1 As System.Windows.Forms.GroupBox
    Friend WithEvents Button_2_Home1 As System.Windows.Forms.Button
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
        Me.Motor1 = New System.Windows.Forms.GroupBox
        Me.Brightlight1 = New System.Windows.Forms.GroupBox
        Me.Button_FullOn1 = New System.Windows.Forms.Button
        Me.Button_Plus1 = New System.Windows.Forms.Button
        Me.Button_Mid1 = New System.Windows.Forms.Button
        Me.Button_Minus1 = New System.Windows.Forms.Button
        Me.Button_Off1 = New System.Windows.Forms.Button
        Me.Value1 = New System.Windows.Forms.TextBox
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.Brightlight1.SuspendLayout()
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
        'Motor1
        '
        Me.Motor1.Location = New System.Drawing.Point(72, 8)
        Me.Motor1.Name = "Motor1"
        Me.Motor1.Size = New System.Drawing.Size(232, 320)
        Me.Motor1.TabIndex = 56
        Me.Motor1.TabStop = False
        Me.Motor1.Text = "Motor 1"
        '
        'Brightlight1
        '
        Me.Brightlight1.Controls.Add(Me.Button_FullOn1)
        Me.Brightlight1.Controls.Add(Me.Button_Plus1)
        Me.Brightlight1.Controls.Add(Me.Button_Mid1)
        Me.Brightlight1.Controls.Add(Me.Button_Minus1)
        Me.Brightlight1.Controls.Add(Me.Button_Off1)
        Me.Brightlight1.Controls.Add(Me.Value1)
        Me.Brightlight1.Location = New System.Drawing.Point(344, 8)
        Me.Brightlight1.Name = "Brightlight1"
        Me.Brightlight1.Size = New System.Drawing.Size(152, 320)
        Me.Brightlight1.TabIndex = 57
        Me.Brightlight1.TabStop = False
        Me.Brightlight1.Text = "BrightLight 1"
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
        'Timer1
        '
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(704, 453)
        Me.Controls.Add(Me.Brightlight1)
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
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.Brightlight1.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

#End Region
    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        SerConnectionRead(serHandle1, REG_USER_STATUS_1, temp)            ' read motor state
        State_1_1.Text = temp

        SerConnectionRead(serHandle1, REG_USER_CURRENT_1, temp)           ' read motor location
        Location_1_1.Text() = temp

        SerConnectionRead(serHandle1, REG_USER_STATUS_2, temp)            ' read motor state
        State_2_1.Text = temp

        SerConnectionRead(serHandle1, REG_USER_CURRENT_2, temp)           ' read motor location
        Location_2_1.Text() = temp

        SerConnectionRead(serHandle3, REG_PWM_ABSOLUTE, temp)            ' read brightlight 1
        Value1.Text() = temp / 10

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


End Class
