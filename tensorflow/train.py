from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import os
import numpy
import tensorflow as tf

images = tf.train.match_filenames_once("../images/*.jpg")
image_queue = tf.train.string_input_producer(images, num_epochs=None, shuffle=True, seed=None, capacity=32, shared_name=None, name=None)

IMAGE_SIZE = 960
IMAGE_PIXELS = IMAGE_SIZE * IMAGE_SIZE
batch_size = 1

x = tf.placeholder(tf.float32, shape=(batch_size, IMAGE_SIZE))

y = tf.placeholder(tf.int32, shape=(batch_size))

