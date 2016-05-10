from __future__ import print_function
import numpy as np
import tensorflow as tf
import math as math


def read_from_csv(filename_queue):
  reader = tf.TextLineReader()
  _, csv_row = reader.read(filename_queue)
  record_defaults = [[""],[0]]
  colFile,  colLabel = tf.decode_csv(csv_row, field_delim=" ", record_defaults=record_defaults)
  features = tf.pack([colFile])  
  label = tf.pack([colLabel])  
  return features, label

def input_pipeline(batch_size, num_epochs=None):
  filename_queue = tf.train.string_input_producer(["./28_dense_labels.txt"], num_epochs=num_epochs, shuffle=True)  
  example, label = read_from_csv(filename_queue)
  min_after_dequeue = 10
  capacity = min_after_dequeue + 3 * batch_size
  example_batch, label_batch = tf.train.shuffle_batch(
      [example, label], batch_size=batch_size, capacity=capacity,
      min_after_dequeue=min_after_dequeue)
  return example_batch, label_batch

file_length = 8 
examples, labels = input_pipeline(file_length, 1)

with tf.Session() as sess:
  tf.initialize_all_variables().run()

  # start populating filename queue
  coord = tf.train.Coordinator()
  threads = tf.train.start_queue_runners(coord=coord)

  try:
    while not coord.should_stop():
      example_batch, label_batch = sess.run([examples, labels])
      print(example_batch)
  except tf.errors.OutOfRangeError:
    print('Done training, epoch reached')
  finally:
    coord.request_stop()

  coord.join(threads) 
