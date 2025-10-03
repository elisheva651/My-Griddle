from input import loader

# open to expend to more interesting input options.
def receive_input():
    should_try_get_input = True

    while (should_try_get_input) :
        path = input("Enter image path: ").strip()
        try:
            loader.load_image()
            loader.save_image()
        except Exception as e:
            print("Error:", e)
            retry = input("Do you want to try to upload an image again? y/n: ").strip().lower()
            if retry :
                should_try_get_input = False


    