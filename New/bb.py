import math
from dataclasses import dataclass
import data


@dataclass
class Bethe_Block:
    
    
    # fixed parameters
    K = 0.307075  # Costante di Bethe-Bloch (MeV·cm²/mol)
    me = 0.511  # Massa dell'elettrone in MeV/c^2
    I = 16.0e-6  # Energia media di ionizzazione (in MeV)
    dx = 0.5 #spessore in cm
    
    data : data

    
    def __init__(self,data_in):
        data_in = data


    def Bethe_Block_scaled(self, beta = data.beta,dE = data.dE, scale = data.scale):
        # fixed parameters
        s_K  = int(self.K  *scale)
        s_me = int(self.me *scale)
        s_I  = int(self.I  *scale)
        s_dx = int(self.dx *scale)

        
        #other parameters 
        s_beta = int(beta * scale) 
        s_gamma = int(1 / math.sqrt(1 - (beta)**2)) * scale
        T_max = int(2 * s_me * (s_beta**2 / scale**2) * (s_gamma**2 / scale**2) / (1 + 2 * s_gamma * s_me + (s_me // s_me)**2))  # Maximum transferable energy

        #Bethe-Bloch   
        s_log = int(math.log(2 * (s_me) * (s_beta**2 / scale**2) * (s_gamma/scale)**2 * T_max // s_I**2))
        linear = beta**2 // s_K
        energy_loss = -dE // s_dx
        z = int(math.sqrt(energy_loss/(linear*(s_log-2*beta**2))))
     
        
        print(f"z = {z:.6f} MeV/cm")
        
        
        
    def Bethe_Block(self, beta = data.beta,dE = data.dE):
        
        scale = 1
        # fixed parameters
        s_K  = self.K  *scale
        s_me = self.me *scale
        s_I  = self.I  *scale
        s_dx = self.dx *scale

        
        #other parameters 
        s_beta = beta * scale
        s_gamma = 1 / math.sqrt(1 - (beta)**2) * scale
        T_max = 2 * s_me * (s_beta**2 / scale**2) * (s_gamma**2 / scale**2) / (1 + 2 * s_gamma * s_me + (s_me // s_me)**2)  # Maximum transferable energy

        #Bethe-Bloch   
        s_log = math.log(2 * (s_me) * (s_beta**2 / scale**2) * (s_gamma/scale)**2 * T_max // s_I**2)
        linear = beta**2 // s_K
        energy_loss = -dE // s_dx
        z = math.sqrt(energy_loss/(linear*(s_log-2*beta**2)))
     
        
        print(f"z = {z:.6f} MeV/cm")
        
        
        

