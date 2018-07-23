Public Class Form1
    Inherits System.Windows.Forms.Form

    Public serHandle1 As Integer    ' motor 1
    Public serHandle2 As Integer    ' motor 2
    Public serHandle3 As Integer    ' brightlight 1
    Public serHandle4 As Integer    ' brightlight 2

    Public temp As Integer


#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call


        ' connect to the brightlight on COM1
        serHandle3 = SerConnectionConnect(1, DEF_BRIGHTLIGHT)         ' connect to port 3, brightlight 1

        While serHandle3 = &H0
            Dim response As MsgBoxResult
            response = MsgBox("COM PORT 1 did not open or connect", MsgBoxStyle.AbortRetryIgnore)
            If response = MsgBoxResult.Retry Then   ' User chose Yes.
                serHandle3 = SerConnectionConnect(1, DEF_BRIGHTLIGHT)   ' connect to port 3, brightlight 1
            ElseIf response = MsgBoxResult.Ignore Then
                Exit While
            Else
                Throw New System.Exception("Program Canceled")
            End If

        End While

        If serHandle3 = &H0 Then
            BrightLight1.Text = "No BrightLight"
        End If

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
    Friend WithEvents Button_FullOn1 As System.Windows.Forms.Button
    Friend WithEvents Button_Plus1 As System.Windows.Forms.Button
    Friend WithEvents Button_Mid1 As System.Windows.Forms.Button
    Friend WithEvents Button_Minus1 As System.Windows.Forms.Button
    Friend WithEvents Button_Off1 As System.Windows.Forms.Button
    Friend WithEvents Value1 As System.Windows.Forms.TextBox
    Friend WithEvents BrightLight1 As System.Windows.Forms.GroupBox
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Me.BrightLight1 = New System.Windows.Forms.GroupBox
        Me.Button_FullOn1 = New System.Windows.Forms.Button
        Me.Button_Plus1 = New System.Windows.Forms.Button
        Me.Button_Mid1 = New System.Windows.Forms.Button
        Me.Button_Minus1 = New System.Windows.Forms.Button
        Me.Button_Off1 = New System.Windows.Forms.Button
        Me.Value1 = New System.Windows.Forms.TextBox
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.BrightLight1.SuspendLayout()
        Me.SuspendLayout()
        '
        'BrightLight1
        '
        Me.BrightLight1.Controls.Add(Me.Button_FullOn1)
        Me.BrightLight1.Controls.Add(Me.Button_Plus1)
        Me.BrightLight1.Controls.Add(Me.Button_Mid1)
        Me.BrightLight1.Controls.Add(Me.Button_Minus1)
        Me.BrightLight1.Controls.Add(Me.Button_Off1)
        Me.BrightLight1.Controls.Add(Me.Value1)
        Me.BrightLight1.Location = New System.Drawing.Point(24, 16)
        Me.BrightLight1.Name = "BrightLight1"
        Me.BrightLight1.Size = New System.Drawing.Size(152, 320)
        Me.BrightLight1.TabIndex = 2
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
        'Timer1
        '
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(576, 429)
        Me.Controls.Add(Me.BrightLight1)
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.BrightLight1.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        SerConnectionRead(serHandle3, REG_PWM_ABSOLUTE, temp)            ' read brightlight 1
        Value1.Text() = temp / 10

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
