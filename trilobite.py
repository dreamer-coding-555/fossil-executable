# trilobite.py
import subprocess

def cube_runner():
    # Run your Meson application using subprocess
    subprocess.run(["./builddir/code/app"])

if __name__ == "__main__":
    cube_runner()
