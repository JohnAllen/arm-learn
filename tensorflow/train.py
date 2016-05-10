from __future__ import print_function
import numpy as np
import tensorflow as tf
import math as math
from PIL import Image

def read_from_csv(filename_queue):
    reader = tf.TextLineReader()
    _, csv_row = reader.read(filename_queue)
    record_defaults = [[""],[0]]
    image_path, label  = tf.decode_csv(csv_row, field_delim=" ", record_defaults=record_defaults)
    image = tf.image.decode_jpeg(image_path, channels=3)
    return image, label 

def input_pipeline(batch_size, num_epochs=None):
    filename_queue = tf.train.string_input_producer(["./28_dense_labels.txt"], num_epochs=num_epochs, shuffle=True)  
    image, label = read_from_csv(filename_queue)
    print("image: ", image)  
    image = tf.reshape(image, [28,28,3])
    print("image: ", image)  
    min_after_dequeue = 5
    capacity = min_after_dequeue + 3 * batch_size
    image_batch, label_batch = tf.train.batch( [image, label], batch_size=batch_size, capacity=capacity)
    return image_batch, label_batch

file_length = 7 
examples, labels = input_pipeline(file_length, 1)

# Parameters
learning_rate = 0.001
training_epochs = 5
batch_size = 1
display_step = 1

# tf Graph Input
x = tf.placeholder("float", [None, 784]) # mnist data image of shape 28*28=784
y = tf.placeholder("float", [None, 10]) # 0-9 digits recognition => 10 classes

# Set model weights
W = tf.Variable(tf.zeros([784, 10]))
b = tf.Variable(tf.zeros([10]))

# Construct model
activation = tf.nn.softmax(tf.matmul(x, W) + b) # Softmax

# Minimize error using cross entropy
cost = tf.reduce_mean(-tf.reduce_sum(y*tf.log(activation),
reduction_indices=1)) # Cross entropy
optimizer = tf.train.GradientDescentOptimizer(learning_rate).minimize(cost) #

with tf.Session() as sess:
  tf.initialize_all_variables().run()
  # start populating filename queue
  coord = tf.train.Coordinator()
  threads = tf.train.start_queue_runners(coord=coord)
  try:
    while not coord.should_stop():
        # Training cycle
        for epoch in range(training_epochs):
            avg_cost = 0.
            # Loop over all batches
            num_batches = int(file_length / batch_size)
            for i in range(num_batches):
                example_batch, label_batch = sess.run([examples, labels])
                # Fit training using batch data
                print(example_batch)
                sess.run(optimizer, feed_dict={x: example_batch, y: label_batch})
                # Compute average loss
                avg_cost += sess.run(cost, feed_dict={x: example_batch, y:
batch_ys})/num_batches
                # Display logs per epoch step
                if epoch % display_step == 0:
                    print ("Epoch:",'%04d' % (epoch+1),"cost=","{:.9f}".format(avg_cost))
  except tf.errors.OutOfRangeError:
      print('Done training, epoch reached')
  finally:
    coord.request_stop()

  coord.join(threads) 
