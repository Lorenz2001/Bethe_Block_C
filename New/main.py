import bb
import data as dt


def main():
    data = dt.data(0.8678938,20)
    result = bb.Bethe_Block(data)
    
    delta = result.Bethe_Block()-result.Bethe_Block_scaled()
    print(f'delta:{delta}')
if __name__ == "__main__":
    main()