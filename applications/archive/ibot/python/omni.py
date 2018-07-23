import clr
import sys
sys.path.append("C:\\Program Files (x86)\\Tecan Systems\\Omni V4.0")
clr.FindAssembly('NrcCmdProc.V2')
from NrcCmdProc.V2 import OmniApi
from NrcCmdProc import OmniErrorCode
import pdb
import numpy as np
import time

class TecanException(Exception):
    '''Raise when the Tecan Robot returns an error'''
    def __init__(self, message, cmd,error, *args):
        self.message = message # without this you may get DeprecationWarning
        # Special attribute you desire with your Error, 
        # perhaps the value that caused the error?:
        self.cmd = cmd #the command the resulted in the error
        self.error = error #the error that was returned
        # allow users initialize misc. arguments as any other builtin Error
        super(TecanException, self).__init__(message, cmd,error, *args) 


class MyTecanApi():
    X = 'M1'
    Y = 'M2'
    Z = 'M3'
    A = 'A0'
    ADP = 'E0'

    def __init__(self,TCP_IP = '192.168.0.198',TCP_PORT= '9898',MY_IP = '192.168.0.20',MY_PORT=9899):
        self.tecan_api = OmniApi()
        error= self.tecan_api.InitOmniApi(TCP_IP,TCP_PORT,MY_IP,MY_PORT)
        print error

    def HasTip(self):
        cmd = self.makeCmd((self.Z+"Get","TipPresence"))
        response = self.sendCmd(cmd)
        return (response.IntValue==1)
    
    def DropTip(self):
        cmd = self.makeCmd((self.ADP+"-1","ER"))
        return self.sendCmd(cmd)

    def PickTip(self,zstart=None,
            zstop = None,
            zaccept = None,
            speed = "",
            force = ""):
        assert(self.HasTip()==False)
        currZ = self.GetPos(self.Z)
        if zstart == None:
            zstart = currZ
        if zstop == None:
            zstop = zstart - 35
        if zaccept == None:
            zaccept = zstart - 1
        assert(not self.HasTip())
            
        cmd = self.makeCmd((self.Z+"PickTip",zstart,zstop,zaccept,speed,force))
        
        return self.sendCmd(cmd)

    def InitializeADP(self):
        cmd = self.makeCmd(('C0Set','EnableCavroCAN','0'))
        self.sendCmd(cmd)
        cmd2 = self.makeCmd((self.ADP+"-1","WR"))
        return self.sendCmd(cmd2)

    def makeCmd(self,mytuple):
        print 'cmd:', ','.join(map(str,mytuple))
        return ','.join(map(str,mytuple))

    def SetPlungerSpeed(self,ul_per_sec=75):
        cmd=self.makeCmd((self.ADP+"-1","V"+str(ul_per_sec),"1R"))
        return self.sendCmd(cmd)

    def IsADPBusy(self):
        cmd = self.makeCmd((self.ADP+"-1","Q0"))
        response = self.sendCmd(cmd)
        print response.ErrorCode
        print response.Comment
 
    def SetupAspirate(self,min_ul=100,moveSpeed=250):
        self.SetPlungerSpeed(moveSpeed)
        self.SetPlungerPosition_ul(min_ul)
        
    def Aspirate(self,ul,speed=75,min_ul=100,searchDistance=2):
        assert(self.HasTip())
        pos = self.GetPlungerPosition_ul()
        assert(pos>min_ul)
        #if pos<min_ul:
        #    self.SetPlungerSpeed(250)
        #    self.SetPlungerPosition_ul(min_ul)
        self.SetPlungerSpeed(speed)
        #self.searchliquid(searchDistance)
        cmd=self.makeCmd((self.ADP+"-1","P"+str(ul),"1R"))
        return self.sendCmd(cmd)

    def SetPlungerPosition_ul(self,ul):
        cmd = self.makeCmd((self.ADP+"-1","A"+str(ul),"1R"))
        return self.sendCmd(cmd)

    def DumpAll(self):
        self.SetPlungerSpeed(75)
        print 'Zero'
        return self.SetPlungerPosition_ul(0)

    def Dispense(self,ul, speed = 175):
        self.SetPlungerSpeed(speed)
        cmd = self.makeCmd((self.ADP+"-1","D"+str(ul),"1R"))
        response=self.sendCmd(cmd)
        return response

    def InitCavro(self,axis='M1'):
        self.sendCmd(axis+"CavroInit")
        response=self.InitializeADP()
        #self.sendCmd(self.makeCmd(('C0Set','EnableCavroCAN',0)))
        return response
    
    def ClearError(self,axis):
        cmd = self.makeCmd((str(axis)+"C"))

    def sendCmd(self,cmd,timeout=-1):
        error=self.tecan_api.SendCmd(cmd,timeout)
        if (error.ErrorCode != 0):
            print error.ErrorCode
            raise(TecanException("Tecan Error in sendCmd",cmd,error))
        return error
    
    def searchliquid(self, searchlim,subdist=4, sensitivity = 3, method = 0, retractonerror = 0):
        startZ = str(self.GetPos(self.Z))
        print startZ
        searchlim = str(searchlim)
        subdist = str(subdist)
        sensitivity = str(sensitivity)
        method = str(method)
        retractonerror = str(retractonerror)
        print searchlim
        cmd = self.makeCmd((self.Z+"DetectLiquid",startZ,searchlim,subdist,sensitivity,method,retractonerror))
        return self.sendCmd(cmd)

    def GetPos(self,axis='M1'):
        return self.sendCmd(axis+"Get,Pos").FloatValue

    def MoveAbs(self,position,axis='M1'):
        return self.sendCmd(axis+"MoveAbs,"+str(position))

    def MoveAbsTuple(self,xyz):
        print xyz
        x,y,z = xyz
        return self.MoveAbsXYZ(x, y, z)
    
    def PickTipAt(self,xyz):
        assert(self.HasTip()==False)
        self.MoveAbsTuple(xyz)
        self.PickTip()
        
    def DropTipAt(self,xyz):
        self.MoveAbsTuple(xyz)
        self.DropTip()

    def MoveAbsXYZ(self,x,y,z):
        xyz=','.join(map(str,(x,y,z)))
        return self.sendCmd("A0MoveAbs,"+xyz)
    
    def GoHome(self):
        x,y,z = 750,0,210
        self.MoveAbsXYZ(x,y,z)

    def GetPosXYZ(self):
        x=self.GetPos(self.X)
        y=self.GetPos(self.Y)
        z=self.GetPos(self.Z)
        return (x,y,z)

    def MoveRel(self,dx,axis='M1'):
        currpos = self.GetPos(axis)
        newpos = currpos + dx 
        return self.MoveAbs(newpos,axis)

    def MoveRelXYZ(self,dx=0,dy=0,dz=0):
        (x,y,z)=self.GetPosXYZ()
        x=x+dx
        y=y+dy
        z=z+dz
        return self.MoveAbsXYZ(x, y, z)

    def MoveTipInPlate(self,tipplate,io,jo,ie,je):

        x,y,z = tipplate.get_well_pos(io,jo)
        self.MoveAbsXYZ(x,y,z)
        self.PickTip()
        x,y,z = tipplate.get_well_pos(ie,je)
        self.MoveAbsXYZ(x,y,z)
        self.DropTip()

    def GetPlungerPosition_ul(self):
        cmd = self.makeCmd((self.ADP+"-6",'?3'))
        response = self.sendCmd(cmd)
        comment_str = str(response.Comment)
        value = float(comment_str[2:])
        return value
  
    def GetAxisSpeed(self,axis='M1'):
        response=self.sendCmd(axis+"Get,DefSpeed")
        return response.FloatValue

    def SetAxisSpeed(self,speed,axis='M1'):
        cmd=self.makeCmd((axis+"Set","DefSpeed",speed))
        response = self.sendCmd(cmd)
        
        
        
        
class TipPlate(object):
    def __init__(self, well00xy, wellNMxy, Z, N , M,tecan = None,tip_matrix=None):
        # well00xy is a (x,y) tuple with the x and y pohttp://localhost:8888/edit/Documents/OmniControl/omni.py#sition of the 0,0 well
        # wellNMxy is a (x,y) tuple with the x,y position of the N,M well
        # Z is the position of the plate
        # N is the number of rows in the plate (rows go in Y vertically)
        # M is the number of columns in the plate (columns go in X horizontally
        self.tecan = tecan
        assert(type(N)==int)
        assert(type(M)==int)

        self.well00xy = map(float,well00xy)
        self.wellNMxz = map(float,wellNMxy)
        self.N = N 
        self.M = M
        self.Z = float(Z)
        
        if tip_matrix is None:
            self.tip_matrix = np.ones((N,M))
        else:
            self.tip_matrix = tip_matrix
        if M>1:
            self.dx = (wellNMxy[0]-well00xy[0])/(M-1)
        else:
            self.dx =0.0
        if N>1:
            self.dy = (wellNMxy[1]-well00xy[1])/(N-1)
        else:
            self.dy =0.0
        print self.dx,self.dy
        
    def get_well_pos(self,i,j):
        # get the xyz tuple of the interpolated position of the well at i,j
        # verify that i,j makes sense for this well
        assert(type(i)==int)
        assert(type(j)==int)
        assert(i>=0)
        assert(j>=0)
        assert(i<self.N)
        assert(j<self.M)

        x,y = self.well00xy
        print x,y

        xn = x + self.dx*j
        yn = y + self.dy*i
        print 'x:',xn,'y:',yn,'z:',self.Z
        

        return (xn,yn,self.Z)
    def take_new_tip(self):
        for i in range(self.N):
            for j in range(self.M):
                if self.tip_matrix[i,j]==1:
                    return self.take_tip(i,j)
                
    def take_tip(self,i,j):
        assert(self.tip_matrix[i,j]==1)
        self.tip_matrix[i,j]=0
        return self.get_well_pos(i,j)
        
    def drop_tip(self,i,j):
        assert(self.tip_matrix[i,j]==0)
        self.tip_matrix[i,j]=1
        return self.get_well_pos(i,j)
    
    
class AntiBodyPlate(TipPlate):
    def __init__(self, well00xy, wellNMxy, Z, N = 8, M = 12):
        """ xy00 is a tuple of the xy coordinates for the first well on the chiller
        xyNM is the location of the final well in the plate (12,8) 
        N is the number of rows of the plate in Y
        M is the number of columns in X, default to a 96 well plate
        Z is the height of the plate in mm"""
        super(self.__class__,self).__init__(well00xy, wellNMxy, Z, N = 8, M = 12)
        self.N = N
        self.M = M
        self.MaxVol = 500
        self.volume_matrix = np.zeros((N,M))
        for m in range(4):
            for n in range(8):
                self.volume_matrix[n,m] = 500 
                
                
        self.Blocktuple = []
        self.Tristuple = []
        self.Glycinetuple = []
        self.Primetuple = []
        self.Secondtuple = []
        for m in range(2):
            for n in range(8):
                    blockij = [n,m]
                    trisij = [n,m+2]
                    glyij = [n,m+3]
                    primeij = [n,m+4]
                    secondij = [n,m+5]
                    self.Blocktuple.append(blockij)
                    self.Tristuple.append(trisij)
                    self.Glycinetuple.append(glyij)
                    self.Primetuple.append(primeij)
                    self.Secondtuple.append(secondij)
                
        """Volume matrix represents the initial amount of fluid present in some of the wells, at a max volume of 500 uL"""
                
        
#         self.Z = Z
#         self.well00xy= well00xy
#         self.wellNMxy = wellNMxy
#         self.dx = dx
#         self.dy = dy
#         assert(type(N) == int)
#         assert(type(M) == int)
#         self.xy00 = map(float,xy00)
#         self.xyNM = map(float,xyNM)
#         self.N = N
#         self.M = M
#         self.Z = float(Z)

#         if M > 1:
#             self.dx = (xyNM[0] - xy00[0])/(M-1)
#         else:
#             self.dx = 0.0

#         if N > 1:
#             self.dy = (xyNM[1] - xy00[1])/(N-1)
#         else:
#             self.dy = 0.0 

#         print self.dx,self.dy
    
    def go_to_wellij(self,i,j):
        return self.get_well_pos(i,j)
    
    def find_full_well(self,asvol,welltuple):
        for n in range(len(welltuple)):
            i,j = welltuple[n]
            if self.volume_matrix[i,j] >= asvol:
                return i,j
            
        
#         assert(type(i)==int)
#         assert(type(j)==int)
#         assert(i>= 0)
#         assert(j>= 0)
#         assert(i< self.N)
#         assert(j< self.M)
#         x,y = self.xy00
        
#         xn = x + self.dx*j
#         yn = y + self.dy*i
#         return (xn,yn,self.Z)
        