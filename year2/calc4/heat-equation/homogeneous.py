import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import quad
from mpl_toolkits.mplot3d import Axes3D

L = 50
alpha = 1

def f(x):
    return 20

def c_m(m):
    integral = np.vectorize(lambda x: f(x) * np.sin(m * np.pi * x / L))
    result, _ = quad(integral, 0, L)
    return (2 / L) * result

def u(x, t, num_terms=50):
    if t == 0:
        return np.full_like(x, f(x))  # u(x, 0) = 20
    else:
        coefficients = [c_m(m) for m in range(1, num_terms + 1)]
        sum_terms = np.zeros_like(x)
        for m in range(1, num_terms + 1):
            cm = coefficients[m - 1]
            term = cm * np.exp(-(m**2 * np.pi**2 * alpha**2 * t) / L**2) * np.sin(m * np.pi * x / L)
            sum_terms += term
        return sum_terms

x_vals = np.linspace(0, L, 100)

t_values = [0, 20, 50, 150, 300]

fig, axes = plt.subplots(1, 2, figsize=(16, 6))

# Plot 3D
X, T = np.meshgrid(x_vals, t_values)
U = np.array([u(x_vals, t) for t in t_values])

ax_3d = fig.add_subplot(122, projection='3d')
ax_3d.plot_surface(X, T, U, cmap='viridis')
ax_3d.set_xlabel('x')
ax_3d.set_ylabel('t')
ax_3d.set_zlabel('u(x, t)')
ax_3d.set_title('3D')

# Plot 2D
for t in t_values:
    u_values = u(x_vals, t)
    axes[0].plot(x_vals, u_values, label=f't = {t}')

axes[0].set_xlabel('x')
axes[0].set_ylabel('u(x, t)')
axes[0].set_title('2D')
axes[0].legend()
axes[0].grid(True)

plt.tight_layout()
plt.show()
