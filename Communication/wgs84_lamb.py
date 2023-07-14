from numpy import sin, sqrt, pi, cos, tan, log

def d2r(angle:float)->float:
    return angle*pi/180

def wgs2lamb(lat:float, long:float):

    if(lat >90 or lat < -90):
        raise ValueError("|Latitude| supérieur à 90°")
    if(long < 0 or long > 180):
        raise ValueError("Longitude non comprise entre 0 et 180°")

    long = d2r(long); lat = d2r(lat)
    f1 = d2r(44); f2 = d2r(49); f0 = d2r(46.5); l0 = d2r(3)
    X0 = 700000; Y0 = 6600000
    a = 6378137; f = 1/(298.257); e = sqrt(2*f-f**2)

    n0 = log(cos(f2)/cos(f1))+0.5*log((1-(e*sin(f1))**2)/(1-(e*sin(f2))**2))
    n1 = tan(f1/2+pi/4)*(1-e*sin(f1))**(e/2)*(1+e*sin(f2))**e/2
    n2 = tan(f2/2+pi/4)*(1+e*sin(f1))**(e/2)*(1-e*sin(f2))**e/2

    n = n0/log(n1/n2)

    p1 = a*cos(f1)/(n*sqrt(1-(e*sin(f1))**2))
    p2 = (tan(f1/2+pi/4)*((1-e*sin(f1))/(1+e*sin(f1)))**(e/2))**n
    p0 = p1*p2

    def p(f:float)->float:
        p3 = (1/tan(f/2+pi/4)*((1-e*sin(f))/(1+e*sin(f)))**(e/2))**n
        return p0*p3
    
    def t(l:float)->float:
        return n*(l-l0)
    print("->")
    print("(",round(X0+p(lat)*sin(t(long)),0),",",round(Y0+p(f0)-p(lat)*cos(t(long)),0),")")

wgs2lamb(eval(input("Latitude : ")), eval(input("Longitutde : ")))
