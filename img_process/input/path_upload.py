from PIL import Image
import numpy as np
import os

from general_constants import IMAGE_SAVE_PATH, IMAGE_SAVE_FILENAME


def load_image(path):
    img = Image.open(path).convert("RGB")
    return np.array(img)

def save_image(arr, path):
    img = Image.fromarray(arr.astype(np.uint8))
    img.save(path)
 
 
# open to expend to more interesting input options.
def receive_input():
    should_try_get_input = True

    while (should_try_get_input) :
        path = input("Enter image path: ").strip()
        try:
            img = load_image(path)

            save_path = os.path.join(IMAGE_SAVE_PATH, IMAGE_SAVE_FILENAME)
            save_image(img, save_path)
            return
        except Exception as e:
            print("Error:", e)
            retry = input("Do you want to try to upload an image again? y/n: ").strip().lower()
            if retry != 'y':
                should_try_get_input = False
