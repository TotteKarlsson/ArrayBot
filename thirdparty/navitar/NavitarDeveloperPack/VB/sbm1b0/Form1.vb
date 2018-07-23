Public Class Form1
    Inherits System.Windows.Forms.Form


    Public serHandle1 As Integer
    Public motorType1 As Integer

    Public temp As Integer




#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

        ' connect to the motor controller on COM1
        serHandle1 = SerConnectionConnect(1, DEF_MOTOR_CONTROLLER)       ' connect to port 1, Motor controller

        While serHandle1 = 0
            Dim response As MsgBoxResult
            response = MsgBox("COM PORT 1 did not open or connect", MsgBoxStyle.RetryCancel)
            If response = MsgBoxResult.Retry Then   ' User chose Yes.
                serHandle1 = SerConnectionConnect(1, DEF_MOTOR_CONTROLLER)         ' connect to port 1, Motor controller
            Else
                Throw New System.Exception("Program Canceled")
            End If

        End While

        ' make sure we connnected. This should be handled with a better message box.
        If serHandle1 = &H100 Then
            Call MsgBox("did not connect to a controller, Exiting", MsgBoxStyle.Critical)
            End
        End If

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

        SerConnectionRead(serHandle1, REG_USER_STATUS_1, temp)            ' read motor state
        State_1_1.Text = temp

        SerConnectionRead(serHandle1, REG_USER_CURRENT_1, temp)            ' read motor location
        Location_1_1.Text() = temp

        SerConnectionRead(serHandle1, REG_USER_STATUS_1, temp)            ' read motor state
        State_2_1.Text = temp

        SerConnectionRead(serHandle1, REG_USER_CURRENT_1, temp)            ' read motor location
        Location_2_1.Text() = temp



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
    Friend WithEvents Button_2_Home As System.Windows.Forms.Button
    Friend WithEvents Button_1_Limit1 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Plus1 As System.Windows.Forms.Button
    Friend WithEvents Button_1_GOTO1 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Minus1 As System.Windows.Forms.Button
    Friend WithEvents Button_1_Home As System.Windows.Forms.Button
    Friend WithEvents State_1_1 As System.Windows.Forms.TextBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents State_2_1 As System.Windows.Forms.TextBox
    Friend WithEvents Location_2_1 As System.Windows.Forms.TextBox
    Friend WithEvents Location_1_1 As System.Windows.Forms.TextBox
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents Motor1 As System.Windows.Forms.GroupBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Me.Button_2_Limit1 = New System.Windows.Forms.Button
        Me.Button_2_Plus1 = New System.Windows.Forms.Button
        Me.Button_2_GOTO1 = New System.Windows.Forms.Button
        Me.Button_2_Minus1 = New System.Windows.Forms.Button
        Me.Button_2_Home = New System.Windows.Forms.Button
        Me.Button_1_Limit1 = New System.Windows.Forms.Button
        Me.Button_1_Plus1 = New System.Windows.Forms.Button
        Me.Button_1_GOTO1 = New System.Windows.Forms.Button
        Me.Button_1_Minus1 = New System.Windows.Forms.Button
        Me.Button_1_Home = New System.Windows.Forms.Button
        Me.State_2_1 = New System.Windows.Forms.TextBox
        Me.Location_2_1 = New System.Windows.Forms.TextBox
        Me.State_1_1 = New System.Windows.Forms.TextBox
        Me.Location_1_1 = New System.Windows.Forms.TextBox
        Me.Label4 = New System.Windows.Forms.Label
        Me.Label3 = New System.Windows.Forms.Label
        Me.Label2 = New System.Windows.Forms.Label
        Me.Label1 = New System.Windows.Forms.Label
        Me.Motor1 = New System.Windows.Forms.GroupBox
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.SuspendLayout()
        '
        'Button_2_Limit1
        '
        Me.Button_2_Limit1.Location = New System.Drawing.Point(224, 288)
        Me.Button_2_Limit1.Name = "Button_2_Limit1"
        Me.Button_2_Limit1.TabIndex = 36
        Me.Button_2_Limit1.Text = "Limit"
        '
        'Button_2_Plus1
        '
        Me.Button_2_Plus1.Location = New System.Drawing.Point(224, 256)
        Me.Button_2_Plus1.Name = "Button_2_Plus1"
        Me.Button_2_Plus1.TabIndex = 35
        Me.Button_2_Plus1.Text = "+ 100"
        '
        'Button_2_GOTO1
        '
        Me.Button_2_GOTO1.Location = New System.Drawing.Point(224, 224)
        Me.Button_2_GOTO1.Name = "Button_2_GOTO1"
        Me.Button_2_GOTO1.TabIndex = 34
        Me.Button_2_GOTO1.Text = "GOTO 1000"
        '
        'Button_2_Minus1
        '
        Me.Button_2_Minus1.Location = New System.Drawing.Point(224, 192)
        Me.Button_2_Minus1.Name = "Button_2_Minus1"
        Me.Button_2_Minus1.TabIndex = 33
        Me.Button_2_Minus1.Text = "- 100"
        '
        'Button_2_Home
        '
        Me.Button_2_Home.Location = New System.Drawing.Point(224, 160)
        Me.Button_2_Home.Name = "Button_2_Home"
        Me.Button_2_Home.TabIndex = 32
        Me.Button_2_Home.Text = "Home"
        '
        'Button_1_Limit1
        '
        Me.Button_1_Limit1.Location = New System.Drawing.Point(112, 288)
        Me.Button_1_Limit1.Name = "Button_1_Limit1"
        Me.Button_1_Limit1.TabIndex = 31
        Me.Button_1_Limit1.Text = "Limit"
        '
        'Button_1_Plus1
        '
        Me.Button_1_Plus1.Location = New System.Drawing.Point(112, 256)
        Me.Button_1_Plus1.Name = "Button_1_Plus1"
        Me.Button_1_Plus1.TabIndex = 30
        Me.Button_1_Plus1.Text = "+ 100"
        '
        'Button_1_GOTO1
        '
        Me.Button_1_GOTO1.Location = New System.Drawing.Point(112, 224)
        Me.Button_1_GOTO1.Name = "Button_1_GOTO1"
        Me.Button_1_GOTO1.TabIndex = 29
        Me.Button_1_GOTO1.Text = "GOTO 1000"
        '
        'Button_1_Minus1
        '
        Me.Button_1_Minus1.Location = New System.Drawing.Point(112, 192)
        Me.Button_1_Minus1.Name = "Button_1_Minus1"
        Me.Button_1_Minus1.TabIndex = 28
        Me.Button_1_Minus1.Text = "- 100"
        '
        'Button_1_Home
        '
        Me.Button_1_Home.Location = New System.Drawing.Point(112, 160)
        Me.Button_1_Home.Name = "Button_1_Home"
        Me.Button_1_Home.TabIndex = 27
        Me.Button_1_Home.Text = "Home"
        '
        'State_2_1
        '
        Me.State_2_1.Location = New System.Drawing.Point(224, 120)
        Me.State_2_1.Name = "State_2_1"
        Me.State_2_1.Size = New System.Drawing.Size(75, 20)
        Me.State_2_1.TabIndex = 26
        Me.State_2_1.Text = "TextBox4"
        '
        'Location_2_1
        '
        Me.Location_2_1.Location = New System.Drawing.Point(224, 80)
        Me.Location_2_1.Name = "Location_2_1"
        Me.Location_2_1.Size = New System.Drawing.Size(75, 20)
        Me.Location_2_1.TabIndex = 25
        Me.Location_2_1.Text = "TextBox3"
        '
        'State_1_1
        '
        Me.State_1_1.Location = New System.Drawing.Point(112, 120)
        Me.State_1_1.Name = "State_1_1"
        Me.State_1_1.Size = New System.Drawing.Size(75, 20)
        Me.State_1_1.TabIndex = 24
        Me.State_1_1.Text = "TextBox2"
        '
        'Location_1_1
        '
        Me.Location_1_1.Location = New System.Drawing.Point(112, 80)
        Me.Location_1_1.Name = "Location_1_1"
        Me.Location_1_1.Size = New System.Drawing.Size(75, 20)
        Me.Location_1_1.TabIndex = 23
        Me.Location_1_1.Text = "TextBox1"
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(24, 80)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(56, 23)
        Me.Label4.TabIndex = 22
        Me.Label4.Text = "Location"
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(24, 120)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(56, 23)
        Me.Label3.TabIndex = 21
        Me.Label3.Text = "State"
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(240, 40)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(56, 23)
        Me.Label2.TabIndex = 20
        Me.Label2.Text = "Axis 2"
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(128, 40)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(48, 23)
        Me.Label1.TabIndex = 19
        Me.Label1.Text = "Axis 1"
        '
        'Motor1
        '
        Me.Motor1.Location = New System.Drawing.Point(88, 16)
        Me.Motor1.Name = "Motor1"
        Me.Motor1.Size = New System.Drawing.Size(232, 320)
        Me.Motor1.TabIndex = 37
        Me.Motor1.TabStop = False
        Me.Motor1.Text = "Motor 1"
        '
        'Timer1
        '
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(864, 469)
        Me.Controls.Add(Me.Button_2_Limit1)
        Me.Controls.Add(Me.Button_2_Plus1)
        Me.Controls.Add(Me.Button_2_GOTO1)
        Me.Controls.Add(Me.Button_2_Minus1)
        Me.Controls.Add(Me.Button_2_Home)
        Me.Controls.Add(Me.Button_1_Limit1)
        Me.Controls.Add(Me.Button_1_Plus1)
        Me.Controls.Add(Me.Button_1_GOTO1)
        Me.Controls.Add(Me.Button_1_Minus1)
        Me.Controls.Add(Me.Button_1_Home)
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
        Me.Text = "1 Motor"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        SerConnectionRead(serHandle1, REG_USER_STATUS_1, temp)            ' read motor state
        State_1_1.Text = temp

        SerConnectionRead(serHandle1, REG_USER_CURRENT_1, temp)            ' read motor location
        Location_1_1.Text() = temp

        SerConnectionRead(serHandle1, REG_USER_STATUS_2, temp)            ' read motor state
        State_2_1.Text = temp

        SerConnectionRead(serHandle1, REG_USER_CURRENT_2, temp)            ' read motor location
        Location_2_1.Text() = temp


    End Sub

    Private Sub Button_1_Home_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_1_Home.Click
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

    Private Sub Button_2_Home_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_2_Home.Click
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

End Class
