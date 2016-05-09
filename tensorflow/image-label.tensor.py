"""A very simple MNIST classifier.
See extensive documentation at
http://tensorflow.org/tutorials/mnist/beginners/index.md
"""
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import os
import tensorflow as tf
from tensorflow.python.framework import ops

flags = tf.app.flags
FLAGS = flags.FLAGS

data_folder = "../images/"
filename = "28_dense_labels.txt"


