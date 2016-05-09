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
from tensorflow.python.framework import dtypes
from tensorflow.python.training import queue_runner

flags = tf.app.flags
FLAGS = flags.FLAGS

data_folder = "../images/"
filename = "28_dense_labels.txt"

#filename = os.path.join(data_folder, data_file)
def dense_to_one_hot(labels_dense, num_classes):
  """Convert class labels from scalars to one-hot vectors."""
  num_labels = labels_dense.shape[0]
  index_offset = numpy.arange(num_labels) * num_classes
  labels_one_hot = numpy.zeros((num_labels, num_classes))
  labels_one_hot.flat[index_offset + labels_dense.ravel()] = 1
  return labels_one_hot

def read_images_from_disk(input_queue):
    """Consumes a single filename and label as a ' '-delimited string.
    Args:
      filename_and_label_tensor: A scalar string tensor.
    Returns:
      Two tensors: the decoded image, and the string label.
    """
    label = input_queue[1]
    file_contents = tf.read_file(input_queue[0])
    example = tf.image.decode_jpeg(file_contents, channels=3)
    return example, label

def read_labeled_image_list(image_list_file):
    """Reads a .txt file containing paths and labels
    Args:
       image_list_file: a .txt file with one /path/to/image per line
    Returns:
       Two lists: filenames and labels
    """
    f = open(image_list_file, 'r')
    filenames = []
    labels = []
    for line in f:
        filename = line.split(None,1)[0]
        label = line.split(None,1)[1]
        filenames.append(filename)
        labels.append(int(label))
    return filenames, labels


def getBatch(filename, batch_size, 
                    processing_image=lambda x: x,
                    processing_label=lambda y: y,
                    num_epochs=None):
    """The input pipeline for reading images classification data.
    The data should be stored in a single text file of using the format:
     /path/to/image_0 label_0
     /path/to/image_1 label_1
     ...
     Args:
       filename: the path to the txt file
       batch_size: size of batches produced
       num_epochs: optionally limited the amount of epochs
    Returns:
        TODO
    """
    # Reads paths of images together with their labels
    image_list, label_list = read_labeled_image_list(filename)
    images = ops.convert_to_tensor(image_list, dtype=dtypes.string)
    labels = ops.convert_to_tensor(label_list, dtype=dtypes.int32)
    # Makes an input queue
    input_queue = tf.train.slice_input_producer([images, labels],
                                                num_epochs=num_epochs,
                                                shuffle=True)
    # Reads the actual images from
    image, label = read_images_from_disk(input_queue)
    print(image)
    pr_image = processing_image(image)
    print(image)
    pr_label = processing_label(label)
    image_batch, label_batch = tf.train.batch([pr_image, pr_label],
                                              batch_size=batch_size)
    # Display the training images in the visualizer.
    tensor_name = image.op.name
    tf.image_summary(tensor_name + 'images', image_batch)
    return image_batch, label_batch


sess = tf.InteractiveSession()
# Create the model
x = tf.placeholder(tf.float32, [None, 784])
W = tf.Variable(tf.zeros([784, 10]))
b = tf.Variable(tf.zeros([10]))
y = tf.nn.softmax(tf.matmul(x, W) + b)

# Define loss and optimizer
y_ = tf.placeholder(tf.float32, [None, 10])
cross_entropy = tf.reduce_mean(-tf.reduce_sum(y_ * tf.log(y), reduction_indices=[1]))
train_step = tf.train.GradientDescentOptimizer(0.5).minimize(cross_entropy)

# Train
tf.initialize_all_variables().run()
for i in range(1):
  batch_xs, batch_ys = getBatch(filename, 1)
  train_step.run({x: batch_xs, y_: batch_ys})

# Test trained model
correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
print(accuracy.eval({x: mnist.test.images, y_: mnist.test.labels}))
