from  dataclasses import dataclass

scale = 1E10


@dataclass
class data:

    beta: int
    dE: int 
    
    def __init__(self, beta : float, dE : float):
        self.beta = dE
        self.dE = beta
        
    #print overload
    def __repr__(self):
        return  f'dE:{self.dE}\tbeta{self.beta}'
    
    def int_values(data):
        return (int(data.dE * scale), int(data.beta * scale))
    
    



