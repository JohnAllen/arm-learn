from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import os
import numpy
import tensorflow as tf


def read_my_file_format(filename_and_label_tensor):
  """Consumes a single filename and label as a ' '-delimited string.
  Args:
    filename_and_label_tensor: A scalar string tensor.

  Returns:
    Two tensors: the decoded image, and the string label.
  """
  
  record_defaults = [tf.constant([], dtype=tf.string), 
                   tf.constant([], dtype=tf.int32),   
                   tf.constant([], dtype=tf.int32)]  
 
  filename, servo_0, servo_1 = tf.decode_csv(filename_and_label_tensor, record_defaults, " ")
  file_contents = tf.read_file(filename)
  example = tf.image.decode_jpeg(file_contents, 1)
  return example, servo_0, servo_1

images = tf.train.match_filenames_once("../images/*.JPG")
image_queue = tf.train.string_input_producer(images, num_epochs=None, shuffle=True, seed=None, capacity=32, shared_name=None, name=None)

IMAGE_SIZE = 150
IMAGE_PIXELS = IMAGE_SIZE * IMAGE_SIZE
batch_size = 1

f = open("paths_labels.txt")
file_lines = f.readlines()

file_queue = tf.train.string_input_producer(file_lines) 
image, servo_0, servo_1 = read_my_file_format(file_queue.dequeue())

x = tf.placeholder(tf.float32, shape=(batch_size, IMAGE_SIZE))
y = tf.placeholder(tf.int32, shape=(batch_size))

#sess = tf.Session()


