from PIL import Image
import numpy as np

def load_image(path):
    img = Image.open(path).convert("RGB")
    return np.array(img)

def save_image(arr, path):
    img = Image.fromarray(arr.astype(np.uint8))
    img.save(path)
 