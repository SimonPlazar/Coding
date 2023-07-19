import numpy as np
import matplotlib.pyplot as plt

def tocka_daljica_projekcija(A, B, P):
    AB = B - A
    AP = P - A
    t = np.sum(AB * AP, axis=1) / np.dot(AB, AB)  # np.sum(AB ** 2) #np.dot(AB, AB)
    t = t.reshape(-1, 1)

    return P - (A + t * AB)

def QuickHull3d(pts):
    pts = np.array(pts)
    x_sorted_indice = np.argsort(pts[:, 0])
    y_sorted_indice = np.argsort(pts[:, 1])
    z_sorted_indice = np.argsort(pts[:, 2])

    x_sorted = pts[x_sorted_indice]
    y_sorted = pts[y_sorted_indice]
    z_sorted = pts[z_sorted_indice]

    X1 = x_sorted[0]
    X2 = x_sorted[-1]

    Y1 = y_sorted[0]
    Y2 = y_sorted[-1]

    Z1 = z_sorted[0]
    Z2 = z_sorted[-1]

    x_norm = np.linalg.norm(X1 - X2)
    y_norm = np.linalg.norm(Y1 - Y2)
    z_norm = np.linalg.norm(Z1 - Z2)

    r1 = X1
    r2 = X2
    temp = x_norm
    if y_norm > temp:
        temp = y_norm
        r1 = Y1
        r2 = Y2
    if z_norm > temp:
        r1 = Z1
        r2 = Z2

    pts_ex = np.array([X1, X2, Y1, Y2, Z1, Z2])
    pts_ex_vectors = tocka_daljica_projekcija(r1, r2, pts_ex)
    pts_ex_norms = np.linalg.norm(pts_ex_vectors, axis=1)

    r3 = pts_ex[np.argmax(pts_ex_norms)]

    V1 = r2 - r1
    V2 = r3 - r1
    Vn = np.cross(V1, V2)

    Vp = pts - r1
    VnVp = np.abs(np.sum(Vn * Vp, axis=1))
    r4 = pts[np.argmax(VnVp)]

    return r1, r2, r3, r4

if __name__ == "__main__":
    pts = np.random.normal(scale=2.0, size=(15, 3))
    hull = pts
    fig = plt.figure()
    ax = plt.axes(projection='3d')

    ax.scatter3D(pts[:, 0], pts[:, 1], pts[:, 2], c=np.linspace(0, pts.shape[0], num=pts.shape[0], endpoint=False),
                 cmap='Greens')

    s1, s2, s3, s4 = QuickHull3d(pts)
    ax.plot3D(*zip(s1, s2), color="red")
    ax.plot3D(*zip(s2, s3), color="red")
    ax.plot3D(*zip(s1, s3), color="red")

    ax.plot3D(*zip(s1, s4), color="red")
    ax.plot3D(*zip(s2, s4), color="red")
    ax.plot3D(*zip(s3, s4), color="red")

    plt.show()