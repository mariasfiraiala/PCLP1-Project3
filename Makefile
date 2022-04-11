#Copyright Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)

CFLAGS=-Wall -Wextra -std=c99

build:
	gcc $(CFLAGS) -o image_editor alloc_utils.c apply.c crop.c exit.c load.c op_utils.c rotate.c save.c select.c image_editor.c -lm
run:
	./image_editor
clean:
	rm -r image_editor
